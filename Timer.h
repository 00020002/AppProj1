
#ifndef TIMERH
#define TIMERH
extern int mins;
extern int secs;
extern int t_running_flag;


void alarm();
void increment_mins();  
void increment_secs();
void disp_time();
void ss_timer();
void reset_timer();


#endif