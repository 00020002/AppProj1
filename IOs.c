/* Name: ENCM 511 Driver Project 4
 * File:   main.c
 * Author: Nicola Primomo & Kun Lu
 *
 * Created on October 25 , 2022
 */

#include "xc.h"
#include "Timer.h"
#include "IOs.h"
#include "TimeDelay.h"


uint16_t b1_flag = 0;
uint16_t b2_flag = 0;
uint16_t b3_flag = 0;


uint16_t b3_pressed = -1;

/* -Configures input/output settings for required pins.
    -Should be called from main.
 */
void IOinit() {


    //Set GPIOs RA2, RA4, and RB4 as inputs
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    TRISBbits.TRISB4 = 1;

    //Enable pull up resistors on pins set as inputs
    CNPU2bits.CN30PUE = 1;
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;

    //Enable CN interrupt on input pins
    CNEN1bits.CN0IE = 1;
    CNEN1bits.CN1IE = 1;
    CNEN2bits.CN30IE = 1;

    //CN Interrupt settings
    IPC4bits.CNIP = 5; //7 is highest priority, 1 is lowest, 0 is disabled interrupt
    IFS1bits.CNIF = 0; // Clear interrupt flag
    IEC1bits.CNIE = 1; //Enable CN interrupts

    //Set GPIO RB8 as output and set low
    TRISBbits.TRISB8 = 0;
    LATBbits.LATB8 = 0;
}

/* -Determines what combination of buttons are pressed and performs required actions.
    -Function will be repeatedly called from main
 *  
 */
void IOcheck() {


    IEC1bits.CNIE = 0; //disable CN interrupts to avoid debounces
    delay_ms(400); // 400 msec delay to filter out debounces 
    IEC1bits.CNIE = 1; //Enable CN interrupts to detect pb release

    LATBbits.LATB8 = 0; //Turns LED off



    if (b1_flag == 1) {
        ///While button 1 pressed:
        // -increment timer minutes
        // -update time on terminal
        while (PORTAbits.RA2 == 0) {
            increment_mins();
            disp_time();
            delay_ms(600);
        }
        b1_flag = 0;
    }




    if (b2_flag == 1) {
        //While button 2 pressed
        // Light on/off with 2 sec delay
        // "PB2 Pressed" sent to terminal
        while (PORTBbits.RB4 == 0) {
            increment_secs();
            disp_time();
            delay_ms(600);
        }
        b2_flag = 0;
    }

    if (b3_flag == 1) { ///While button 3 pressed
        // Light on/off with 3 sec delay
        // "PB3 Pressed" sent to terminal
        
        b3_pressed = 0;
        while(PORTAbits.RA4 == 0)
        {
            if (b3_pressed >= 3) {
            t_running_flag = 0;
            reset_timer();
            disp_time();
            break;
            }
            delay_ms(1000);
            b3_pressed++;
        }
        
        if (t_running_flag == 0 && b3_pressed < 3) {
            t_running_flag = 1;
            ss_timer();
        }


        b3_flag = 0;

    }





}



///// Change of pin Interrupt subroutine

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    IFS1bits.CNIF = 0; // clear IF flag

    if ((PORTAbits.RA2 == 0) && (PORTAbits.RA4 == 1) && (PORTBbits.RB4 == 1)) {
        b1_flag = 1;
        b2_flag = 0;
        b3_flag = 0;
    } else if ((PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 1) && (PORTBbits.RB4 == 0)) {
        b1_flag = 0;
        b2_flag = 1;
        b3_flag = 0;
    } else if ((PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 0) && (PORTBbits.RB4 == 1)) {

        b1_flag = 0;
        b2_flag = 0;
        b3_flag = 1;
        if (t_running_flag == 1) {
            t_running_flag = 0;
        }
    }
 else {
    b1_flag = 0;
    b2_flag = 0;
    b3_flag = 0;
}
return;
}