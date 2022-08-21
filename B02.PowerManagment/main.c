/*
 * File:   main.c
 */

#include <xc.h>
#include "external_interrupt.h"
#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    LED_ARRAY1 = 0x00;
    LED_ARRAY1_DDR = 0x00;
    
    init_ext_int();

    /* Enable all the Global Interrupts */
    GIE = 1;
}

void main(void) {
    unsigned char count = 9;
    unsigned long i;
    unsigned char key;
    
    init_config();

    while (1) {
        if (count != 0)
        {
            // LED2 will toggle till count becomes 0. After that systems goes to sleep
            LED2 = !LED2;
            for (i = 100000; i--; );
            
            count--;
        }
        else
        {
            count = 9;
            /* Put system to sleep. System resumes when interrupt occurs
             * Press a switch to generate interrupt.
             */
            SLEEP();
        }
    }
    return;
}
