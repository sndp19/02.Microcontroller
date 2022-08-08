
/*
 * File: 
 * Author: Sandeep Varma Geddada
 * Created on:   
 * description: 
 */

#include <xc.h>
#include "main.h"

#pragma config WDTE = OFF       //Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    LED1_DDR = 0x00;
    LED1 = 0x00;
}

void main(void) {
    unsigned int delay = 0;
    init_config();
    LED1 = 0x55;
    while (delay++ == 5000) {
         
        LED1 = ~LED1;
        delay = 0;        
    }
    return;
}
