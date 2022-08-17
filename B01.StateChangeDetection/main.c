/*
 * File:   main.c
 */

#include <xc.h>
#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)

static void init_config(void) {
    LED1 = OFF;
    LED1_DDR = 0;
    SW1_DDR = 1;
}

void main(void) {
    int once = 1;
    unsigned long int delay =20000;
    init_config();

    while (1) {
        if ((SW1 == PRESSED) && once)
        {
		if(delay-- == 0)
		{
            		LED1 = !LED1;
            
           		once = 0,delay = 20000;
		}
        }
        else if (SW1 == RELEASED)
        {
            once = 1;
        }
    }
    return;
}
