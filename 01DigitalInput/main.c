/*
 * File:   main.c
 * Author: Wimera 
 *
 * Created on 17 August, 2023, 2:04 PM
 */

#include "xc.h"
#include <stdio.h> 
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <p24FJ256GL406.h>
#define BAUDARATE  9600
#define FOSC (long)32000000
#define FCY (long)FOSC/2
#include <libpic30.h>
#include "uart.h"
#define BufferSize  20
#define NO_OF_DIGITAL_IO_PINS 8
#define BUFFERSIZE  100
#define ON 1
#define OFF 0
#define FAILED 1
#define SUCCESS 0
uint8_t DigitalIO;
typedef struct __attribute__((packed)){
    uint8_t DigitalpinNo;
    uint8_t ON_OFF;
}Pin_No;
Pin_No Digital_IO_Info[NO_OF_DIGITAL_IO_PINS]={{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}};
char Transmit[BUFFERSIZE];

// FBOOT
#pragma config BTMODE = SINGLE          //Boot Mode Configuration bits->Device is in Single Boot (legacy) mode
// FSEC
#pragma config BWRP = ON                // Boot Segment Write-Protect bit (Boot Segment is write protected)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF         // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)

// FOSCSEL
#pragma config FNOSC = PRIPLL           // Oscillator Source Selection (Primary Oscillator with PLL module (XT + PLL, HS + PLL, EC + PLL))
#pragma config PLLMODE = PLL96DIV2      // PLL Mode Selection (96 MHz PLL. Oscillator input is divided by 2 (8 MHz input))
#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FOSC
#pragma config POSCMD = XT              // Primary Oscillator Mode Select bits (XT Crystal Oscillator mode)
#pragma config OSCIOFCN = OFF           // OSC2 Pin Function bit (RC15 (CLKO) outputs CPU clock)
#pragma config SOSCEN = OFF              // SOSC Power Selection Configuration bits (SOSC crystal driver is enabled (SOSCI/SOSCO mode))
#pragma config PLLSS = FRC              // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration bit (Allow only one reconfiguration)
#pragma config FCKSM = CSECME           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are enabled)

// FWDT
#pragma config WDTPS = PS8192          // Watchdog Timer Postscaler bits (1:32,768)
#pragma config FWPSA = PR128            // Watchdog Timer Prescaler bit (1:128)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bits (WDT is always enabled (cannot be controlled by SWDTEN))
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (WDT in non-windowed mode)
#pragma config WDTWIN = WIN75           // Watchdog Timer Window Select bits (WDT window is 75% of WDT period)
#pragma config WDTCMX = WDTCLK          // WDT MUX Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)

// FPOR
#pragma config BOREN = ON               // Brown Out Enable bit (Brown Out is enabled)
#pragma config LPREGEN = OFF            // Low power regulator control (Low power regulator is disabled)
#pragma config LPBOREN = ON             // Downside Voltage Protection Enable bit (Low power BOR is enabled when BOR is inactive)

// FICD
#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGEC2 and PGED2)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config BTSWP = OFF              // BOOTSWP Instruction Enable bit (BOOTSWP instruction is disabled)

// FDMTIVTL
#pragma config DMTIVTL = 0xFFFF         //  (Enter Hexadecimal value)

// FDMTIVTH
#pragma config DMTIVTH = 0xFFFF         //  (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         //  (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         //  (Enter Hexadecimal value)

// FDMT
#pragma config DMTDIS = OFF             //  (Dead Man Timer is disabled and can be enabled by software)

// FDEVOPT1
#pragma config ALTCMPI = OFF            // Alternate Comparator Input Enable bit (C2INC and C3INC are on RG9 and RD11)
#pragma config TMPRPIN = OFF            // Tamper Pin Enable bit (TMPRN pin function is disabled)
#pragma config SOSCHP = ON              // SOSC High Power Enable bit (valid only when SOSCSEL = 1 (SOSC high power mode (default))
#pragma config ALTI2C1 = ON             // Alternate I2C pin Location (ASDA1 and ASCL1 on RB5 and RB4)
#pragma config SMB3EN = ON              // SMBus 3 Enable bit (SMBus 3.0 input levels)

void Clock_Initialization(void) {


    OSCTUN = 0b000000; // setting the oscillator frequency to default
    // Clock switch to incorporate PLL
    __builtin_write_OSCCONH(0x03); // initiate clock switch
    __builtin_write_OSCCONL(OSCCON | 0x01); // start the clock switching operation

    while (OSCCONbits.COSC != 0b011); // checking that the current oscillator has switched to primary osc with PLL
    while (OSCCONbits.LOCK != 1); // waiting for the PLL to get locked

} 
void PIN_Initialization(void)
{    

        /* Digital IO pins initialization */
        TRISFbits.TRISF0 = 1;
        TRISDbits.TRISD7 = 1;
        TRISEbits.TRISE0 = 1;
        TRISFbits.TRISF1 = 1;
        TRISEbits.TRISE2 = 1;
        TRISEbits.TRISE1 = 1;
        TRISEbits.TRISE4 = 1;
        TRISEbits.TRISE3 = 1;
        ANSDbits.ANSD7   = 0;
        ANSEbits.ANSE4   = 0;        
        ANSEbits.ANSE3   = 0;      

     
        TRISBbits.TRISB1 = 1; //Making RB15 as Output direction
        TRISBbits.TRISB2 = 1; //Making RB14 as Input direction

        ANSBbits.ANSB1 = 0; //Making pin RB15 act as Digital pin
        ANSBbits.ANSB2 = 0; //Making pin RB15 act as Digital pin


        __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

        _U2RXR = 13; //RB2->RX2->UART2 
        _RP1R = _RPOUT_U2TX; //RB1->TX2->UART2 

        __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

    
/* LED 2,3,4 pins initialization */
    TRISEbits.TRISE5 = 0;
    TRISEbits.TRISE6 = 0;
    TRISEbits.TRISE7 = 0;

}

uint8_t Digital_IO_check(uint8_t DigitalIO)
{ 
    switch(DigitalIO)  
            {
                case 0:
                {
                    if(!PORTFbits.RF0) 
                    {
                        Digital_IO_Info[DigitalIO].ON_OFF = ON;                        
                    }
                    else
                        Digital_IO_Info[DigitalIO].ON_OFF = OFF;                 
                    break;
                }
                case 1:
                {
                    if(!PORTDbits.RD7)
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;                       
                    }
                    else 
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }
                case 2:
                {
                    if(!PORTEbits.RE0)
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;                        
                    }
                    else
                        Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }
                case 3:
                {
                    if(!PORTFbits.RF1)
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }
                case 4:
                {
                    if(!PORTEbits.RE2)
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;                

                    break;
                }
                case 5:
                {
                    if(!PORTEbits.RE1 )
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;                        
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }
                case 6:
                {
                    if(!PORTEbits.RE4) 
                    {  
                        Digital_IO_Info[DigitalIO].ON_OFF = ON; 
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }case 7:
                {
                    if(!PORTEbits.RE3)
                    {
                        Digital_IO_Info[DigitalIO].ON_OFF = ON;                        
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;
                    break;
                }
                default :
                {
                    return FAILED;
                } 
            }
     
    return SUCCESS;
}
int main(void) {    
 
    Clock_Initialization();
    PIN_Initialization();
    UART_Initialization(BAUDARATE, OneStopBit, EightBitParity);
    uint8_t Digital_IO_Pin =0;
    while(1)
    {   
        //   !PORTEbits.RE0 !PORTFbits.RF1  !PORTEbits.RE2  !PORTEbits.RE1  !PORTEbits.RE4  !PORTEbits.RE3         
                 
    
            for(Digital_IO_Pin = 0; Digital_IO_Pin < NO_OF_DIGITAL_IO_PINS; Digital_IO_Pin++)
            {                 
                if(Digital_IO_check(Digital_IO_Pin) == SUCCESS)
                {   
                    if(Digital_IO_Info[Digital_IO_Pin].ON_OFF )
                        sprintf(Transmit,"Digital IO pin Number %u is ON                  \r\n",Digital_IO_Info[Digital_IO_Pin].DigitalpinNo);   //Storing A/D value into a buffer 
                    else
                        sprintf(Transmit,"Digital IO pin Number %u is OFF                 \r\n",Digital_IO_Info[Digital_IO_Pin].DigitalpinNo);   //Storing A/D value into a buffer   
                }   
                else
                    sprintf(Transmit,"Error                 \r\n");   // 
           
                TransmitReceive((uint8_t*)Transmit,(uint8_t )strlen(Transmit));  
                Digital_IO_Info[Digital_IO_Pin].ON_OFF = OFF;
                __delay_ms(500);
                
            }
            LATEbits.LATE5 =    ~LATEbits.LATE5;
            LATEbits.LATE6  =   ~LATEbits.LATE6;
            LATEbits.LATE7  =   ~LATEbits.LATE7;        
        __delay_ms(10);
        ClrWdt(); 
    }
    return 0;
}




/*
                  
 
 */
/*
    switch(DigitalIO)  
            {
                case 0:
                {
                    Digital_IO_Info[DigitalIO].DigitalIO_pinNo = DigitalIO+1;
                    if(!PORTFbits.RF0) 
                    {
                        Digital_IO_Info[DigitalIO].ON_OFF = ON;                        
                    }
                    else
                        Digital_IO_Info[DigitalIO].ON_OFF = OFF;                 
                    break;
                }
                case 1:
                {
                    Digital_IO_Info[DigitalIO].DigitalIO_pinNo = DigitalIO+1;
                    if(!PORTDbits.RD7)
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;                       
                    }
                    else 
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }
                case 2:
                {
                    Digital_IO_Info[DigitalIO].DigitalIO_pinNo = DigitalIO+1;
                    if(!PORTEbits.RE0)
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;                        
                    }
                    else
                        Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }
                case 3:
                {
                    Digital_IO_Info[DigitalIO].DigitalIO_pinNo = DigitalIO+1;
                    if(!PORTFbits.RF1)
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }
                case 4:
                {
                    Digital_IO_Info[DigitalIO].DigitalIO_pinNo = DigitalIO+1;
                    if(!PORTEbits.RE2)
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;                

                    break;
                }
                case 5:
                {
                    Digital_IO_Info[DigitalIO].DigitalIO_pinNo = DigitalIO+1;
                    if(!PORTEbits.RE1 )
                    {
                       Digital_IO_Info[DigitalIO].ON_OFF = ON;                        
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }
                case 6:
                {
                    Digital_IO_Info[DigitalIO].DigitalIO_pinNo = DigitalIO+1;
                    if(!PORTEbits.RE4) 
                    {  
                        Digital_IO_Info[DigitalIO].ON_OFF = ON; 
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;

                    break;
                }case 7:
                {
                    Digital_IO_Info[DigitalIO].DigitalIO_pinNo = DigitalIO+1;
                    if(!PORTEbits.RE3)
                    {
                        Digital_IO_Info[DigitalIO].ON_OFF = ON;                        
                    }
                    else
                       Digital_IO_Info[DigitalIO].ON_OFF = OFF;
                    break;
                }
                default :
                {
                    return FAILED;
                } 
            }
 
 
 
        if (DigitalIO == 0) {
        if (!PORTFbits.RF0) {
            Digital_IO_Info[DigitalIO].ON_OFF = ON;
        } else
            Digital_IO_Info[DigitalIO].ON_OFF = OFF;

    } else if (DigitalIO == 1) {
        if (!PORTDbits.RD7) {
            Digital_IO_Info[DigitalIO].ON_OFF = ON;
        } else
            Digital_IO_Info[DigitalIO].ON_OFF = OFF;

    } else if (DigitalIO == 2) {
        if (!PORTEbits.RE0) {
            Digital_IO_Info[DigitalIO].ON_OFF = ON;
        } else
            Digital_IO_Info[DigitalIO].ON_OFF = OFF;

    } else if (DigitalIO == 3) {
        if (!PORTFbits.RF1) {
            Digital_IO_Info[DigitalIO].ON_OFF = ON;
        } else
            Digital_IO_Info[DigitalIO].ON_OFF = OFF;

    } else if (DigitalIO == 4) {
        if (!PORTEbits.RE5) {
            Digital_IO_Info[DigitalIO].ON_OFF = ON;
        } else
            Digital_IO_Info[DigitalIO].ON_OFF = OFF;

    } else if (DigitalIO == 5) {
        if (!PORTEbits.RE1) {
            Digital_IO_Info[DigitalIO].ON_OFF = ON;
        } else
            Digital_IO_Info[DigitalIO].ON_OFF = OFF;

    } else if (DigitalIO == 6) {
        if (!PORTEbits.RE4) {
            Digital_IO_Info[DigitalIO].ON_OFF = ON;
        } else
            Digital_IO_Info[DigitalIO].ON_OFF = OFF;

    } else if (DigitalIO == 7) {
        if (!PORTEbits.RE3) {
            Digital_IO_Info[DigitalIO].ON_OFF = ON;
        } else
            Digital_IO_Info[DigitalIO].ON_OFF = OFF;

    } else {
        return FAILED;
    }               
       
 
 */