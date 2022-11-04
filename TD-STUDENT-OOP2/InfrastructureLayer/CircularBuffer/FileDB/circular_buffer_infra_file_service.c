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

/*
#ifndef I_CIRCULAR_BUFFER_REPOSITORY_H
#define I_CIRCULAR_BUFFER_REPOSITORY_H

#include "class.h"

CLASS(circular_buffer);

int ICircularBufferRepository_save(circular_buffer circular_buffer);

// circular_buffer ICircularBufferRepository_get_nth_wheel(int rank);

// int ICircularBufferRepository_delete_nth_buffer(int rank);

void ICircularBufferRepository_close();

int ICircularBufferRepository_open();

void IcircularBufferRepository_append(circular_buffer record);
// twoWheels IDigitalWheelRepository_get_nth_two_wheels(int rank);

#endif
*/

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

// int IDigitalWheelRepository_save(twoWheels two)
// {
//     digital_wheel w1 = two->wheel1;
//     digital_wheel w2 = two->wheel2;
//     if (!IDigitalWheelRepository_open(FILE_DB_REPO))
//         return 0;
//     IDigitalWheelRepository_append(w1);
//     IDigitalWheelRepository_append(w2);

//     return 1;
// }

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

    //FOR FIXING
    printf("\nstore in: %s\n", name);

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

void ICircularBufferRepository_append(circular_buffer record)
{
    /* TO COMPLETE
    -Write record into data_stream
    -Write position where record is written in data_stream and where it stop in index_stream
    */
   circular_buffer temp_buffer_write = record;
   struct index index;
   //int myRecord[5] = {record->current, record->head, record->isFull, record->length, record->tail};
   
   fseek(data_stream, 0L, SEEK_SET);

   index.recordStart = ftell(data_stream);
   index.recordLength = sizeof(record);

   printf("\nindex.recordStart: %ld\n", index.recordStart);
   printf("\nindex.recordLength: %ld\n", index.recordLength);

   fwrite(temp_buffer_write, sizeof(struct circular_buffer), 1, data_stream);

//    printf("\ntemp_buffer_write inside append: %c\n", CircularBuffer_get_char_before_current(temp_buffer_write));

   fseek(index_stream, 0L, SEEK_SET);

   fwrite(&index, sizeof(struct index), 1, index_stream);

   // Test file reading
//    struct index index_read;
//    fseek(index_stream, 0L, SEEK_SET);
//    fread(&index_read, sizeof(struct index), 1, index_stream);
//    printf("\nindex_read.recordStart: %ld\n", index_read.recordStart);
//    printf("\nindex_read.recordLength: %ld\n", index_read.recordLength);
//    fseek(data_stream, index_read.recordStart, SEEK_SET);
//    circular_buffer temp_buffer_read = (struct circular_buffer*)malloc(sizeof(struct circular_buffer));
//    fread(temp_buffer_read, sizeof(struct circular_buffer), 1, data_stream);
//    printf("\ntemp_buffer_read inside get: %c\n", CircularBuffer_get_char_before_current(temp_buffer_read));
}

circular_buffer ICircularBufferRepository_get()
{
    struct index index_read;
    fseek(index_stream, 0L, SEEK_SET);
    fread(&index_read, sizeof(struct index), 1, index_stream);
    printf("\nindex_read.recordStart: %ld\n", index_read.recordStart);
    printf("\nindex_read.recordLength: %ld\n", index_read.recordLength);
    fseek(data_stream, index_read.recordStart, SEEK_SET);
    circular_buffer temp_buffer_read = (struct circular_buffer*)malloc(sizeof(struct circular_buffer));
    fread(temp_buffer_read, sizeof(struct circular_buffer), 1, data_stream);
    // printf("\ntemp_buffer_read inside get: %c\n", CircularBuffer_get_char_before_current(temp_buffer_read));
    return temp_buffer_read;
}

// digital_wheel IDigitalWheelRepository_get_nth_wheel(int rank)
// {
//     struct index index;
//     long shift = (rank - 1) * sizeof index;
//     fseek(index_stream, shift, SEEK_SET);
//     fread(&index, sizeof index, 1, index_stream);
//     fseek(data_stream, index.recordStart, SEEK_SET);
//     int myRecord[3];

//     fread(myRecord, sizeof myRecord, 1, data_stream);
//     //digital_wheel dw = malloc(sizeof(struct digital_wheel));
//     digital_wheel dw = DigitalWheel_construct(myRecord[0], myRecord[1]);
//     DigitalWheel_change_current_position(dw, myRecord[2]);

//     //dw->start = myRecord[0];
//     //dw->end = myRecord[1];
//     //dw->current = myRecord[2];
//     return dw;
// }
