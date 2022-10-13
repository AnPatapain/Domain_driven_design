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

