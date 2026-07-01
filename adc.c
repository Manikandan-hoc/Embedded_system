/*
 * File:   main.c
 * Author: vasan
 *
 * Created on June 24, 2026, 11:48 AM
 */


#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void UART_Init(void)
{
    TRISC6 = 1;      // TX pin
    TRISC7 = 1;      // RX pin

    SPBRG = 129;     // 9600 baud @ 20MHz

    BRGH = 1;        // High speed
    SYNC = 0;        // Async mode
    SPEN = 1;        // Enable serial port

    TXEN = 1;        // Enable transmitter
    CREN = 1;        // Enable receiver
}

/*------------------------------------------------------------------
 Send One Character
------------------------------------------------------------------*/
void UART_SendChar(char c)
{
    while(TXIF == 0);

    TXREG = c;
}

/*------------------------------------------------------------------
 Send String
------------------------------------------------------------------*/
void UART_SendString(const char *s)
{
    while(*s)
    {
        UART_SendChar(*s++);
    }
}

void ADC_Init(void)
{
    TRISA0=1;
    ADCON1=0X80;
    ADCON0=0X81;
   
}

unsigned int ADC_Read(unsigned char channel)
{
    unsigned int result ;
    ADCON0 &= 0xc5;
    ADCON0 |= (channel << 3);
    
    __delay_us(20);
    
    
    GO_DONE = 1;
    
    while(GO_DONE);
    
    result = ((unsigned int) ADRESH << 8)|ADRESL ;
    
    return result;
    
    
}
 
void main(void)
{
    unsigned int adcValue;
    char uartBuffer[30];

    UART_Init();
    ADC_Init();

    UART_SendString("\r\nADC Started\r\n");

    while(1)
    {
        adcValue = ADC_Read(0);

        sprintf(uartBuffer,
                "ADC Value = %u\r\n",
                adcValue);

        UART_SendString(uartBuffer);

        __delay_ms(500);
    }
}