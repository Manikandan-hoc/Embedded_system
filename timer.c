/*
 * File:   timer.c
 * Author: vasan
 *
 * Created on June 23, 2026, 10:21 AM
 */


#include <xc.h>

#define _XTAL_FREQ 4000000


// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF         // Data EEPROM Memory Code Protection bit (Data EEPROM code-protected)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF          // Flash Program Memory Code Protection bit (All program memory code-protected)


void __interrupt() ISR(void)
{       
    if (TMR0IF)
    {
        TMR0IF=0;     //clear interrupt flag
        
        TMR0=61;    //reload value 
        
        RB0=!RB0;  //toggle led
        
    }
}

void main (void)

{
        TRISB0=0;
        TRISB1=0;
        
        RB0=0;
        RB1=0;
        
        
        OPTION_REG=0x07;
        
        TMR0=61;
       
       T0IE=1;
       GIE=1;
      
       
       while(1)
       {
         
        RB1=0;
        RB0=1; 
        __delay_ms(1000);
        
        RB0=0;
        RB1=1;
        __delay_ms(1000);

       }
   
}
