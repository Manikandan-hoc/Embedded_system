#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#define CS RC6         

void SPI_Init()
{
    TRISC3 = 0;     
    TRISC4 = 1;    
    TRISC5 = 0;      

    TRISC6 = 0;      
    CS = 1;          

    SSPSTAT = 0x40;
    SSPCON = 0x20;
}

unsigned char SPI_Write(unsigned char data)
{
    SSPBUF = data;

    while(!SSPIF);

    SSPIF = 0;

    return SSPBUF;
}

void main()
{
    SPI_Init();

    while(1)
    {
        CS = 0;               

        SPI_Write(0x55);   

        CS = 1;               

        __delay_ms(1000);
    }
}
