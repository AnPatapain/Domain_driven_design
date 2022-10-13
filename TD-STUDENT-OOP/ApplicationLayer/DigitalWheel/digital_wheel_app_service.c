//TO COMPLETE
//TO COMPLETE
#include <stdio.h>
#include "digital_wheel_app_service.h"
#include "digital_wheel.h"
#include "class.h"
#include "instantiate.h"

void digitalWheel_run_useCase(digital_wheel self, int rolling_speed){

    while(rolling_speed > 0){
        if(!digital_wheel_move_to_next_position(self)){
            printf("\nNew round...");
        }
        rolling_speed--;
    }

    for (int i = 0; i < rolling_speed; i++) {
        
    }

}

static void display(int wheel_value){
    printf("[ %d ]", wheel_value);
}


// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include "circular_buffer_app_service.h"

// static circular_buffer cb;

// static void generate_next_int()
// {
//     printf("\n[%d]: ", generator_get_next());
// }

// static circular_buffer create(int length)
// {

//     circular_buffer cb = circularBuffer_construct(length);

//     return cb;
// }

// void circularBufferAppService_run_use_case(int c)
// {
//     if (cb == NULL)
//         generate_next_int();

//     switch (c)
//     {
//     case GO_TO_HEAD:
//         circularBuffer_set_current_to_head(cb);
//         break;

//     case DISPLAY_PRECEDENT:
//         printf("(%c)", circularBuffer_get_char_before_current(cb));
//         break;

//     case DESTROY_CIRCULAR_BUFFER:
//         circularBuffer_collect(cb);
//         break;

//     case NEW_CIRCULAR_BUFFER:
//         cb = create(CIRCULAR_BUFFER_LENGTH);
//         break;

//     case '\n':
//         generate_next_int();
//     case ' ':
//     case '\t':
//         break;

//     default:
//         circularBuffer_append_char_at_head(cb, c);
//         break;
//     }
// }
