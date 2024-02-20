#include "uart.h"
#include <string.h>

#define FOSC (long)32000000
#define FCY (long)FOSC/2
#define BRGVAL_SPEED(SPEED)  (((FCY/(SPEED))/16) - 1)
static uint8_t Uartbuffer[BUFFERSIZE] = {0};// Buffer2[BUFFERSIZE] = {0};
unsigned int index1,index2, Uart_flag; //i = 0,RemainingBytes,

/* UART Initialization */
void UART_Initialization(long baudrate, UartStopbits StopBit, UartParityBit ParityBit) {

    //INTCON2bits.GIE = 1; 
    U2STAbits.UTXEN = 0;
    U2MODEbits.STSEL = 0; // 1-Stop bit
    U2MODEbits.PDSEL = 0b00; // No Parity, 8-Data bits
    U2MODEbits.ABAUD = 0; // Auto-Baud disabled
    U2MODEbits.BRGH = 0; // Standard-Speed mode
    U2BRG = BRGVAL_SPEED(baudrate); // Baud Rate setting for 9600    
    U2STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U2STAbits.UTXISEL1 = 0;
    U2STAbits.URXISEL0 = 0; //Interrupt is set when any character is received and transferred from the RSR to the receive buffer
    U2STAbits.URXISEL1 = 0;
    //U2STAbits.URXEN = 1;
    U2MODEbits.UARTEN = 1; // Enable UART
    //Interrupt Enabling
    U2STAbits.UTXEN = 1;
    //IEC1bits.U2RXIE = 1;

    //IPC7bits.U2RXIP = 7;
    IPC7bits.U2TXIP = 6;
    IFS1bits.U2TXIF = 0;
    //IFS1bits.U2RXIF = 0;
    //Storing Buffer base 

}

/* Transmitting data and Enabling Uart Tx interrupt*/
void TransmitReceive(uint8_t *Transmit,uint8_t len) {
    memcpy(Uartbuffer,Transmit,len);
    index1 = len;
    U2TXREG = Uartbuffer[index2++]; //Writing first chat to start Transmitting cycle  
    Uart_flag = 0;
    IEC1bits.U2TXIE = 1;            //Enabling Transfer interrupt

}

/* Transmission with Interrupts*/
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {


    U2TXREG = Uartbuffer[index2++]; //Storing character from buffer to Transmit buffer register     

    if ((index2 >=index1 )) {
        //index1 = 0;
        index2 = 0;
        memset(Uartbuffer, '\0', sizeof (Uartbuffer)); //Clearing buffer             
        IEC1bits.U2TXIE = 0;

    }
    IFS1bits.U2TXIF = 0; //Clearing transmission interrupts   

}


