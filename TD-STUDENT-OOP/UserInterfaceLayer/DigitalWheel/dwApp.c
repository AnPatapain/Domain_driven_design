<<<<<<< HEAD
/*******Compléter****/

#include<stdio.h>
#include<stdlib.h>
#include "digital_wheel_app_service.h"

static void render_menu() {
    puts("************************************");
    puts("* Instance digital wheel created *");
    puts("************************************");
    puts("*************************************************************************");
    puts("At any time you could input a string of char then Enter, e.g, [1]: 1234 ");
    puts("*************************************************************************");
    puts("********************************************************************************************************");
    puts("* Menu [ n: new rotation, Ctr-D: Quit] *");
    puts("********************************************************************************************************");
}

int main() {

    render_menu();
    return EXIT_SUCCESS;

}

=======
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "digital_wheel_two_wheels_app_service.h"
static void f(int v)
{
    printf("[%d]", v);
}

static void display(twoWheels two_wheels)
{
    printf("<");
    DigitalWheelAppService_two_wheels_display(two_wheels, f);
    printf(">\n");
}
int main(int argc, char **argv)
{
    twoWheels two_wheels = DigitalWheelAppService_two_wheels_construct(0, 9);
    DigitalWheelAppService_two_wheels_initialize(two_wheels);
    display(two_wheels);
    DigitalWheelAppService_two_wheels_move(two_wheels, 1, 2);
    display(two_wheels);
    DigitalWheelAppService_two_wheels_move(two_wheels, 1, 2);
    display(two_wheels);
}
>>>>>>> origin/master
