/*
 * File: 
 * Author: Sandeep Varma Geddada
 * Created on:   
 * description: 
 */

#include <xc.h>
#include "ssd.h"
#pragma config WDTE = OFF       //Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    
     init_ssd( );
}

void main(void) {
    unsigned int count = 0, delay = 1000;
    unsigned char ssd[MAX_SSD_COUNT],digit[]= {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
    init_config();
    
    while (1) {
         
        if(delay-- ==0)
        {
            delay = 40000;
            count++;
            if(count > 999)
                count = 0;
            ssd[0] = digit[(count/1000)];
            ssd[1] = digit[(count%1000)/100];
            ssd[2] = digit[(count%100)/10];
            ssd[3] = digit[(count%10)]; 
            display(ssd) ;
        }
               
    }
    return;
}
