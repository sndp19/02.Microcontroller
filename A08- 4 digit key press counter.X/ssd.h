/* 
 * File:   ssd.h
 * Author: Sndp
 *
 * Created on 12 August, 2022, 3:11 PM
 */

#ifndef SSD_H
#define	SSD_H

#define MAX_SSD_COUNT     4


#define SSD_DATA_PORT_DDR           TRISD
#define SSD_CONTROL_PORT_DDR        TRISA

#define SSD_DATA_PORT               PORTD
#define SSD_CONTROL_PORT            PORTA

/*For Switch */
#define SW1_DDR             TRISB0
#define SW2_DDR             TRISB1

#define SW1                 RB0
#define SW2                 RB1

#define ON                  1
#define OFF                 0

#define PRESSED             0
#define RELEASED            1 
/*For Common Cathode Display*/
#define ZERO     0x3F
#define ONE      0x06
#define TWO      0x5B
#define THREE    0x4F
#define FOUR     0x66
#define FIVE     0x6D
#define SIX      0x7D
#define SEVEN    0x07
#define EIGHT    0x7F
#define NINE     0x6F


void init_ssd(void);
void display_ssd(unsigned char data[]);



#endif	/* SSD_H */

