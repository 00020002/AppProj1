/*
 * File:   Timer.c
 * Author: nicol
 *
 * Created on November 13, 2022, 6:25 PM
 */


#include "xc.h"
#include "Timer.h"
#include "TimeDelay.h""

int mins = 0;
int secs = 0;
int t_running_flag = 0;
void decrement_mins(){

    mins--;
           if(mins < 0){
               mins = 0;
           }

}

void decrement_secs(){

    secs--;
           if(secs < 0){
               decrement_mins();
               secs = 59; 
           }
}

void increment_mins(){

    mins++;
           if(mins > 59)
               mins = 0;

}

void increment_secs(){
    secs++;
           if(secs > 59)
               secs = 0;

}


void disp_time()
{
    Disp2Dec(mins);
    Disp2String("m : ");
    Disp2Dec(secs);
    Disp2String("s\n\r");
}

void ss_timer(){
    Disp2String("SS \n\r");
    
        while(t_running_flag == 1 && (mins > 0 || secs > 0)){
        LATBbits.LATB8 = 1;
        decrement_secs();
        disp_time();
        delay_ms(1000);
        LATBbits.LATB8 = 0;
        delay_ms(1000);
    }
        t_running_flag = 0;
    }
    
    
    
  

void reset_timer(){
    mins = 0;
    secs = 0;
    t_running_flag = 0;
    
}

