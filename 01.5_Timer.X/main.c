/*
 * File:   main.c
 * Author: Wimera 
 *
 * Created on 31 August, 2023, 11:50 AM
 */


#include "xc.h"
unsigned int timer_overflow_count = 0;
volatile static uint32_t timerMillis = 0;

#define TIMER1RESOLUTION    65536
#define FOSC (long)32000000
#define FCY (long)FOSC/2 
/*
 *@brief TimerGetMillis function
 * This function return timer count in milli seconds value
 * 
 * @param       :   None
 * @return      :   Milli second count from start of timer
 */
uint32_t TimerGetMillis(void) {
    return timerMillis;
}
/*
 * @brief TimerPeriod function
 * This function is used to calculate PR1value for specific time period and prescaler received  
 * 
 * @param TimePeriod    : time period in ms to be configured
 * @param prescaler     : scaling ratio to be configured
 * @return              : value to be stored in PR2 register
 */
uint32_t TimerPeriod(float TimePeriod, uint16_t prescalers) {
    uint32_t PR1value;
    PR1value =  ((TimePeriod * FOSC) / (2 * prescalers));     
    return PR1value;
}
/*
 *@brief Timer_initialization functions
 * This function contains Timer register initialization  
 * 
 * @param       :   None
 * @return      :   None
 */
void Timer_Initialization(void) {
    T1CON = 0x000;
    //Storing required value in a variable(timer_overflow_count) for 1:64 pre-scaler and 1 ms as time period for tick/timer interrupt 
    timer_overflow_count = TimerPeriod(0.001, 256) -1; 
    //configuring PR1 register to received value  by TimerPeriod function
    PR1 = timer_overflow_count;// pre-scale value
    //Timer1 Input Clock Pre-scale Select bits configured to 1:64
    T1CONbits.TCKPS = 0b11;  //0b10  
    //enable the timer interrupt
    IFS0bits.T1IF = 0;
    IPC0bits.T1IP = 0b111;
    IEC0bits.T1IE = 1;
    //enable timer
    T1CONbits.TON = 1;    
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt() {
     
    if ((IEC0bits.T1IE == 1) && (IFS0bits.T1IF == 1)) {
                
        //Reloading the pre-scale value
        PR1 = timer_overflow_count;
        timerMillis++;
         
        if ( timerMillis >= 100 && timerMillis % 100 == 0 ) {
            LATEbits.LATE5 = ~LATEbits.LATE5;
            /*if(timerMillis >4294967295)
                timerMillis = 0*/
        }      
        IFS0bits.T1IF = 0;
    }

}
void Clock_Initialization(void) {


    OSCTUN = 0b000000; // setting the oscillator frequency to default
    // Clock switch to incorporate PLL
    __builtin_write_OSCCONH(0x03); // initiate clock switch
    __builtin_write_OSCCONL(OSCCON | 0x01); // start the clock switching operation

    while (OSCCONbits.COSC != 0b011); // checking that the current oscillator has switched to primary osc with PLL
    while (OSCCONbits.LOCK != 1); // waiting for the PLL to get locked

} 
int main(void) {
    Clock_Initialization();
    Timer_Initialization();
    TRISEbits.TRISE5  =   0;
    while(1);
    return 0;
}
