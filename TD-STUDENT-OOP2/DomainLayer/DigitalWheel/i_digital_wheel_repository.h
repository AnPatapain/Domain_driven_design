#ifndef I_DIGITAL_WHEEL_REPOSITORY_H
#define I_DIGITAL_WHEEL_REPOSITORY_H

#include "class.h"

CLASS(digital_wheel);
CLASS(twoWheels);
int IDigitalWheelRepository_save(twoWheels twoheels);
digital_wheel IDigitalWheelRepository_get_nth_wheel(int rank);
int IDigitalWheelRepository_delete_nth_wheel(int rank);
void IDigitalWheelRepository_close();
int IDigitalWheelRepository_open();
void IDigitalWheelRepository_append(digital_wheel record);
twoWheels IDigitalWheelRepository_get_nth_two_wheels(int rank);
#endif