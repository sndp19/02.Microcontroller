/*
 * File:   main.c
 * Author: CodeForThings
 * Description: This program will toggle the LEDs at PORTD
 * It illustrates coding practices and conventions used in this course.
 */

#include <xc.h>
#include "main.h"

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)

/* Function: init_config()
 * Description: This function is used to setup initial peripheral
 * configuration, like setting port directions, initializing port values
 */
static void init_config(void) {
    LED_ARRAY1_DDR = 0x00; // Set direction to o/p
    LED_ARRAY1 = 0x00;     // Set initial port value
}

void main(void) {
    unsigned int wait = 0,i,delay=10;
    
    init_config();

    while (1 ) 
	{
       	if(wait++ == 10000)
		{
			wait = 0;
			if(i < 8  && delay-- == 0)
			{
			    LED_ARRAY1 = LED_ARRAY1 | (1 << i++);
                delay=10;
                
			}
			if ((i > 7 && i < 16) && delay-- == 0)                 
			{
			    LED_ARRAY1 = LED_ARRAY1 & ~(1 << ((i++) -8));
                delay=10;
                
			} 
			if((i > 15 && i < 24 ) && delay-- == 0)
			{
			    LED_ARRAY1 = LED_ARRAY1 | (0x80 >> ((i++) -16));
                delay=10;
			}
            if((i > 23 && i < 32 ) && delay-- == 0)
			{
			    LED_ARRAY1 = LED_ARRAY1 & (~(0x80) >> ((i++) -24));
                delay=10;
			}
            if( i ==32)
                i = 0;            
			 
		}
        
          
    }
    return;
}
