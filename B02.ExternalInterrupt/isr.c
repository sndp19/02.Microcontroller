#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
    if (INTF == 1)
    {
        LED1 = !LED1;
        
        INTF = 0;
    }
}