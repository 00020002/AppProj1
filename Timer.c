/* Name: ENCM 511 App Project 1 
 * File:   Timer.c
 * Author: Nicola Primomo & Kun Lu
 *
 * Created on November 16 , 2022
 */
#include "UART2.h"
#include "xc.h"
#include "Timer.h"
#include "TimeDelay.h"
#include "IOs.h"
int mins = 0;
int secs = 0;
int t_running_flag = 0;

void decrement_mins() {
    mins--;
    if (mins < 0) {
        mins = 0;
    }
}

void decrement_secs() {
    delay_ms(1000);
    secs--;
    if (secs < 0) {
        decrement_mins();
        secs = 59;
    }
}

void increment_mins() {

    mins++;
    if (mins > 59)
        mins = 0;

}

void increment_secs() {
    secs++;
    if (secs > 59)
        secs = 0;

}

void disp_time() {
    Disp2String("\033[2K");
    Disp2String("\r");
    Disp2Dec(mins);
    Disp2String("m : ");
    Disp2Dec(secs);
}

void ss_timer() {
    while (t_running_flag == 1) {
        decrement_secs();
        if(secs == 0 && mins == 0) break;
        LATBbits.LATB8 = 1;
        disp_time();
        delay_ms(1000);
        LATBbits.LATB8 = 0;
    }
    t_running_flag = 0;
    if(b3_pressed >= 3){
        reset_timer();
        disp_time();
    }
    
    if (mins == 0 && secs == 0)
    {
        alarm();
    }
        
}

void alarm() {
    disp_time();
    Disp2String(" -- ALARM");
        LATBbits.LATB8 = 1;
        Idle();
}

void reset_timer() {
    mins = 0;
    secs = 0;
    t_running_flag = 0;

}

