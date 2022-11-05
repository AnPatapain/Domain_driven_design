#ifndef I_CIRCULAR_BUFFER_REPOSITORY_H
#define I_CIRCULAR_BUFFER_REPOSITORY_H

#include "class.h"

CLASS(circular_buffer);

int ICircularBufferRepository_save(circular_buffer circular_buffer);

void ICircularBufferRepository_close();

int ICircularBufferRepository_open();

void ICircularBufferRepository_append(circular_buffer record);

circular_buffer ICircularBufferRepository_get_nth_buffer(int);

#endif