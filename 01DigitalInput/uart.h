/*************************************************************************
 * 
 * WIMERA CONFIDENTIAL
 * __________________
 * 
 *  [2022-23] - WIMERA SYSTEMS PVT. LIMITED
 *  All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of WIMERA SYSTEMS PVT. LIMITED. The intellectual and 
 * technical concepts contained  herein are proprietary to 
 * WIMERA SYSTEMS PVT. LIMITED. may be covered by Patents, patents in process, 
 * and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from WIMERA SYSTEMS PVT. LIMITED.
 ************************************************************************/
/* 
 * File:   uart.h
 * Author: Wimera
 *
 * Created on 21 September, 2023, 7:24 AM
 */



#ifndef UART_H
#define	UART_H
#include <xc.h>
#ifdef	__cplusplus

#endif

#define BUFFERSIZE  100
    typedef enum UartParity {
        EightBitParity = 0b00,
        EightBitEvenParity = 0b01,
        EightBitOddParity = 0b10,
        NineBitParity = 0b11
    } UartParityBit;

    typedef enum Stopbit {
        OneStopBit = 0b0,
        TwoStopBit = 0b1
    } UartStopbits;

   
    void UART_Initialization(long baudrate, UartStopbits StopBit, UartParityBit ParityBit);
    void TransmitReceive(uint8_t *Transmit,uint8_t len);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

