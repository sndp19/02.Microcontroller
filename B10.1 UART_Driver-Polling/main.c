/*
 * File:   main.c
 */

#include <xc.h>
#include "uart.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_uart(9600);
    
    puts("UART Test Code\n\r");
}

void main(void) {
    unsigned char ch;
    
    init_config();

    while (1) {
        ch = getchar();
        putchar(ch);
    }
    return;
}
