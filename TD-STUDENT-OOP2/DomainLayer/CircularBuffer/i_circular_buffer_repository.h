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

circular_buffer ICircularBufferRepository_get();
// twoWheels IDigitalWheelRepository_get_nth_two_wheels(int rank);

#endif