/*
 * File:   main.c
 */

#include <xc.h>
#include "external_interrupt.h"
#include "main.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    LED_ARRAY1 = 0x00;
    LED_ARRAY1_DDR = 0x00;
    
    init_ext_int();
    init_digital_keypad();
    /* Enable all the Global Interrupts */
    GIE = 1;
}

void main(void) {
    unsigned long i;
    unsigned char key;
    
    init_config();

    while (1) {
        // Get key press value   ===> Polling method 
        key = read_digital_keypad(STATE);
        
        if (key == SW1)
        {
            LED2 = !LED2;
        }
        
        /* Blocking delay, will cause event loss.
         * If users presses key now, it will not be detected
         */
        for (i = 100000; i--; );
    }
    return;
}
