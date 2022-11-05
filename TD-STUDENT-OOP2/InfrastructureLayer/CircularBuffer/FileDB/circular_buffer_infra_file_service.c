#include<stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "i_circular_buffer_repository.h"
#include "circular_buffer_infra_file_service.h"
#include "i_circular_buffer.h"
#define INDEX_SUFFIX ".ndx"
#define DATA_SUFFIX ".rec"
#define FILE_DB_REPO "./Persistence/FileDB/BUFFER"

struct RECORD_CB
{
    unsigned long data_length;
    int offset_head;
    int offset_current;
    char data[1000]; //new in c99 !!
};

struct circular_buffer
{
    char *tail;
    unsigned long length;
    char *head;
    char *current;
    bool isFull;
};

struct index
{
    long recordStart;
    size_t recordLength;
};

static FILE *index_stream;
static FILE *data_stream;

int ICircularBufferRepository_save(circular_buffer circular_buffer)
{
    if(!ICircularBufferRepository_open(FILE_DB_REPO)){
        return 0;
    }
    ICircularBufferRepository_append(circular_buffer);
    return 1;
}

void ICircularBufferRepository_close(void)
{
    fclose(data_stream);
    fclose(index_stream);
}

static FILE *auxiliary_open(char *prefix, char *suffix)
{
    int prefix_length = strlen(prefix);
    int suffix_length = strlen(suffix);
    char name[prefix_length + suffix_length + 1];
    strncpy(name, prefix, prefix_length);
    strncpy(name + prefix_length, suffix, suffix_length + 1);

    FILE *stream = fopen(name, "r+");
    if (stream == NULL)
        stream = fopen(name, "w+");
    if (stream == NULL){
        perror(name);
    }
        
    return stream;
}

int ICircularBufferRepository_open(char *name)
{
    data_stream = auxiliary_open(name, DATA_SUFFIX);
    if (data_stream == NULL)
        return 0;
    index_stream = auxiliary_open(name, INDEX_SUFFIX);
    if (index_stream == NULL)
    {
        fclose(index_stream);
        return 0;
    }
    return 1;
}

void ICircularBufferRepository_append(circular_buffer buffer_to_save) {
    struct RECORD_CB* record = (struct RECORD_CB*)malloc(sizeof(struct RECORD_CB));

    //Store offset
    record->data_length = buffer_to_save->length;
    record->offset_head = (buffer_to_save->head - buffer_to_save->tail)/sizeof(char);
    record->offset_current = (buffer_to_save->current - buffer_to_save->tail)/sizeof(char);
    
    //Store data
    char *traversing_temp = buffer_to_save->head - 1;
    int i = record->offset_head - 1;
    while(traversing_temp != buffer_to_save->tail - 1){
        record->data[i] = *traversing_temp--;
        i -= 1;
    }

    //Save to persistence database
    struct index index;
    fseek(data_stream, 0L, SEEK_END);
    index.recordStart = ftell(data_stream);
    index.recordLength = sizeof(struct RECORD_CB);
    fwrite(record, sizeof(struct RECORD_CB), 1, data_stream);
    fseek(index_stream, 0L, SEEK_END);
    fwrite(&index, sizeof(struct index), 1, index_stream);

    // FOR TESTING
    // printf("\nindex start: %d, index length: %d\n", index.recordStart, index.recordLength);
    // printf("\ninside Iappend\n");
    // printf("data_length: %d offset_head: %d offset_current: %d", record->data_length, record->offset_head, record->offset_current);
    // printf("\ndata\n");
    // for(int j=0; j < record->offset_head; j++) {
    //     printf("\n%c\n", record->data[j]);
    // }

}

circular_buffer ICircularBufferRepository_get_nth_buffer(int rank) {
    //retrieve index stored in BUFFER.ndx
    struct index index_read;
    int file_pointer_shift = sizeof(index_read) * (rank-1);
    fseek(index_stream, file_pointer_shift, SEEK_SET);
    fread(&index_read, sizeof(struct index), 1, index_stream);

    //retrieve record stored in form of struct RECORD_CB in BUFFER.rec
    fseek(data_stream, index_read.recordStart, SEEK_SET);
    struct RECORD_CB* record = (struct RECORD_CB*)malloc(sizeof(struct RECORD_CB));
    fread(record, sizeof(struct RECORD_CB), 1, data_stream);

    //Construct buffer based on record
    circular_buffer buffer = (circular_buffer)malloc(sizeof(struct circular_buffer));
    buffer = CircularBuffer_construct(record->data_length);

    for(int i=0; i < record->offset_head; i++) {
        CircularBuffer_append_char_at_head(buffer, record->data[i]);
    }

    //FOR TESTING
    // printf("\ninside Iget\n");
    // printf("\nindex start: %d, index length: %d\n", index_read.recordStart, index_read.recordLength);
    // printf("data_length: %d offset_head: %d offset_current: %d", record->data_length, record->offset_head, record->offset_current);
    // printf("\ndata\n");
    // for(int j=0; j < record->offset_head; j++) {
    //     printf("\n%c\n", record->data[j]);
    // }
    
    return buffer;
}

