/*
 * File:   main.c
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_clcd();
    init_matrix_keypad() ;
    
    clcd_print("Select MKP Key:",LINE1(0));    //
    clcd_print("S1-Right S2-Left",LINE2(0));    //
}

void main(void) {
    unsigned char key,key_backup;
    char arr[16] = " G_Sandeep_Varma ",temp,i;
    
    init_config();

    while (1) {
    
        key = read_matrix_keypad(STATE);
        if(key != ALL_RELEASED)
            key_backup = key;
        if(key_backup == 6)             //Right-Scrolling
        {
            clcd_print("Right Scrolling",LINE1(0));
            //Logic:Right Scrolling
            temp = arr[15];
            for(i=15 ; i>0;i--)
                arr[i] = arr[i-1];
            arr[0] = temp;
            clcd_print(arr,LINE2(0));                       
           
        }
        else if(key_backup == 4)        //Left Scrolling
        {
            clcd_print("Left Scrolling",LINE1(0));
            //Logic : Left Scrolling
            temp = arr[0];
            for(i=0;i<15;i++)
                arr[i] = arr[i+1];
            arr[15] = temp;
            clcd_print(arr,LINE2(0));
            
        }    
    }
    return;
}
