/*
 * name: Sandeep Varma Geddada
 * date: 19/8/2022
 * description: A08 - Implement a 4 digit key press counter
 */
 

#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"
#pragma config WDTE = OFF       //Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) 
{
    init_ssd( );
}
//Need to use IRQ and use read_digital_keypad
void main(void) {
    unsigned long int delay = 0;
    static int count = 0;
    unsigned char key,key1,once =1;
    unsigned char ssd[MAX_SSD_COUNT],digit[]= {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
    init_config();
    
    while (1) {
        /* Checking if switch pressed is Edge triggered or below 2sec*/ 
        if ((SW1 ==  PRESSED)&& once)
        {
           if(delay-- ==0)
           {
                delay = 10000;
                count++;
                if(count > 999)
                    count = 0;
                ssd[0] = digit[(count/1000)];
                ssd[1] = digit[(count%1000)/100];
                ssd[2] = digit[(count%100)/10];
                ssd[3] = digit[(count%10)]; 
                display_ssd(ssd) ;          //Passing ssd array to SSD display function
                 
            }
          
            //for (unsigned long int wait = 20000; wait--; );
        }
        /* Checking if switch pressed is Level triggered or above 2sec*/ 
        else if( SW1 == PRESSED )
            count = 0;
           
    }
    return;
}
