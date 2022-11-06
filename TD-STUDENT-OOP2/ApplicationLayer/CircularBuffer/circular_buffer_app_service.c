#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "circular_buffer_app_service.h"
#include "i_circular_buffer_repository.h"

#define FILE_DB_REPO "../Persistence/FileDB/BUFFER"

static circular_buffer cb;
//static circular_buffer cb;
static void generate_next_int()
{
    printf("\n[%d]: ", generator_get_next());
}

static void create(int length)
{
    cb = CircularBuffer_construct(length);
}

void CircularBufferAppService_run_use_case(int c)
{
    if (cb == NULL)
        generate_next_int();

    switch (c)
    {
    case GO_TO_HEAD:
        CircularBuffer_set_current_to_head(cb);
        break;

    case DISPLAY_PRECEDENT:
        printf("(%c)", CircularBuffer_get_char_before_current(cb));
        break;

    case DESTROY_CIRCULAR_BUFFER:
        CircularBuffer_collect(cb);
        break;

    case NEW_CIRCULAR_BUFFER:
        create(CIRCULAR_BUFFER_LENGTH);
        break;

    case SAVE:
        ICircularBufferRepository_save(cb);
        ICircularBufferRepository_close();
        printf("\n SUCESSFULLY SAVED\n");
        // printf("\nSUCESSFULLY SAVED address object cb: %c\n", CircularBuffer_get_char_before_current(cb));
        break;

    case READ:
        if (ICircularBufferRepository_open(FILE_DB_REPO)) {
            int rank;
            scanf("%d", &rank);
            circular_buffer temp_cb = ICircularBufferRepository_get_nth_buffer(rank);
            cb = temp_cb;
            printf("\nSUCESSFULLY READ\n");
            // printf("\nREAD SUCESSFULLY address object cb: %c\n", CircularBuffer_get_char_before_current(cb));
        }
        else {
            printf("\ncan not retrieve to database\n");
        }
        
        break;

    case '\n':
        generate_next_int();
    case ' ':
    case '\t':
        break;

    default:
        CircularBuffer_append_char_at_head(cb, c);
        break;
    }
}
