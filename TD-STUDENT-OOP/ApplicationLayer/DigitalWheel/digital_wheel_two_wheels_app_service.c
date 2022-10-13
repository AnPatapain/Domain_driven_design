#include <stdlib.h>
#include "instantiate.h"
#include "digital_wheel_two_wheels_app_service.h"

struct twoWheels
{
    digital_wheel wheel1;
    digital_wheel wheel2;
};

static void display(digital_wheel wheel, void (*f)(int));

