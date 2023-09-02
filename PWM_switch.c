/*
 * File:   PWM_switch.c
 * Author: udits
 *Aim:Generate PWM on RC2 and change the duty cycle when the key is pressed,
  if S1(RB4) switch is pressed 5% Duty cycle will Increase and if S2(RB5) switch is pressed 5% cycle will decrease.
 * Created on 2 September, 2023, 10:25 AM
 */


#include <xc.h>
#define _XTAL_FREQ 6000000
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void init(void);
unsigned int value=0;

void main(void) {
    unsigned char x;
    init();
    while(1)
    {
       x=PORTB;
       if((x & 0x10)==0x10)
       {
          value=value+19;
          __delay_ms(200);
        
       }
       if((x & 0x20)==0x20)
       {
           if(value<=19)
           {
               value=0;
           }
           else
           {
               value=value-19;
           }
           __delay_ms(200);
           
       }
       CCP1CON=(CCP1CON&0xCF)+((value&0x03)<<4);
       CCPR1L=(value)>>2;
       __delay_ms(100);
    }
    return;
}
void init(void)
{
    TRISB=0xFF;//directing as a input
    TRISC=0x00;//directing as a output
    CCP1CON=0x0C;
    CCPR1L=0x00;
    T2CON=0x06;
    PR2=0x5D;
}
