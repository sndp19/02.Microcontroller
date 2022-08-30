/*
 * File:   main.c
 */

#include <xc.h>
#include "digital_keypad.h"
//#include "clcd.h"
#include "ssd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned char eeprom_test(unsigned char key)
{
    static unsigned char count = 0;
    
    if (key == SW1)
    {
        eeprom_write(0x00, count);
    }
    else if (key == SW2)
    {
        count = eeprom_read(0x00);
    }
    //count upto 9 on every key press(DKP3).
    //Once count exceeds 9 lets Roll back to 0.
    else if (key == SW3)
    {
        if (count++ == 9)
        {
            count = 0;
        }
    }
    
    return count;
}

static void init_config(void) {
    init_digital_keypad();
    init_ssd();
  
}

void main(void) {
    unsigned char key, count;
    unsigned char ssd[MAX_SSD_CNT];
    unsigned char digits[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
                          //     0     1   2    3       4     5    .......................
    init_config();

    while (1) {
        key = read_digital_keypad(STATE);
        
        count = eeprom_test(key);
        
        //Count Display
        ssd[3] = digits[count%10]; // count%10 : 7 : digits[count%10] : digits[7]
        ssd[2] = digits[(count/10)%10]; //count/10 : 456%10 : 6
        ssd[1] = digits[(count/100)%10]; //count/100: 45%10 : 5
        ssd[0] = digits[count/1000]; /
        display(ssd);
      
    }
    return;
}
