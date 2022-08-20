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
    init_config();

    while (1) {
        ;
    }
    return;
}
