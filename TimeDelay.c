/* Name: ENCM 511 App Project 1 
 * File:   TimeDelay.c
 * Author: Nicola Primomo & Kun Lu
 *
 * Created on November 16 , 2022
 */


#include "xc.h"
#include "TimeDelay.h"
/* 
 * -delay_ms function modified from class notes
 * -generates delay is ms equal to time_ms argument
 * -Uses a 1:256 Clock Prescaler and assumes 8Mhz internal clock is being used
 * 
 */
void delay_ms(uint16_t time_ms){
    T2CONbits.T32 = 0; //Timer2 and Timer3 act as separate timers
    T2CONbits.TCS = 0; //Clock source is internal clock
    T2CONbits.TCKPS = 0b11; //Input Clock Prescaler = 1:256
    T2CONbits.TSIDL = 0; //Timer2 continues in idle
    
    IPC1bits.T2IP = 7; //interrupt priority = 7(highest) 
    IEC0bits.T2IE = 1;//Enables Timer2 interrupts
    IFS0bits.T2IF = 0; //clear interrupt flag
    
    int divisor = 1000 / 64;
    int cycles = (time_ms) * divisor;
    
    PR2 = cycles;
    TMR2 = 0x0000;
    
    T2CONbits.TON = 1;
    
    
    Idle();

    T2CONbits.TON = 0;
    return;
}

//Timer 2 Interrupt Routine
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0; //clear interrupt flag
    T2CONbits.TON = 0;//stops timer2
}