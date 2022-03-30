#include <kipr/botball.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/functions.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/consts.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/timer.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/run_functs.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/threads.h>
void starting_claw(){
  slow_servo(claw,claw_max,1);
  msleep(1600);
}
void thread_starting_pos(){
  thread starting_pos;
  starting_pos = thread_create(starting_claw);
  thread_start(starting_pos);
  slow_servo(shifter,shifter_ver, 1);
  msleep(1000);
  slow_servo(arm,arm_max,1);
  thread_destroy(starting_pos);
}
///////////////////////////////////////////
void open_pom(){
  slow_servo(claw, claw_max,1);
}
void thread_grab_pom(){
  thread pom;
  pom = thread_create(open_pom);
  thread_start(pom);
  slow_servo(arm, 300, 1);
  msleep(300);
  slow_servo(claw,claw_min,2);
  thread_destroy(pom);
}
///////////////////////////////////////////