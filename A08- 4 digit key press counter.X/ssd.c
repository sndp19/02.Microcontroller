#include <xc.h>
#include "ssd.h"
void init_ssd(void)
{
    /*Setting the ssd data line as Output (RD0 to RD7)*/
    SSD_DATA_PORT_DDR = 0x00;
    
    /*Setting SSD Control lines as Output (RA2-RA5)*/ //RA2 RA3 RA4 RA5
    SSD_CONTROL_PORT_DDR = SSD_CONTROL_PORT_DDR & 0X03; // TRISA = TRISA & 0x03; = xxxx xxxx & 0000 0011 = 0000 00xx
    
    //SSD_CONTROL_PORT = SSD_CONTROL_PORT & 0x03;
        
}

void display_ssd(unsigned char data[])
{
    unsigned long int delay=0 ;
    int digit;
    
    for (digit = 0;digit < MAX_SSD_COUNT;digit++)
    {
        //if( delay-- == 0)
        //{
            SSD_DATA_PORT = data[digit];
            SSD_CONTROL_PORT = (SSD_CONTROL_PORT & 0x03) | (0x04 << digit);//Making sure all PORTA (RA2-RA5) are zero and doing shift operation
            delay = 20000;
        //}   
        for (unsigned long int wait = 20000; wait--; );       
        
    }
    
    
    
    
}
