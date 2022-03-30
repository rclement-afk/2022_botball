#include <kipr/botball.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/functions.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/consts.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/timer.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/threads.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/run_functs.h>
#include </home/root/Documents/KISS/Default User/CW Clone/include/clone_consts.h>
void god_start(){
  prime_or_clone();
  calibrate_gyro();
  thread_starting_pos();
 // wait_light();
  return grab_rings();
  //return ring_stand_return();
}
void column_run(){
   Drive(-1500,-50);
   square_up(1,-400);
   slow_servo(shifter,shifter_hor,1);
   Drive(2680,50);
   slow_servo(arm,arm_min+150,1);
   msleep(800);
   slow_servo(claw,claw_max,1);
   msleep(800);
   Drive(-1600,-50);
   square_up(2,-400);
}
void ring_loop(int lower){
   int speed = 500;
   int d_speed = speed/10;
   slow_servo(shifter,shifter_ver,1);
   slow_servo(arm,arm_min-lower,1); //-200
   Drive(1500,50);
   turn_with_gyro(speed,1,0); 
   Drive(800,50);
   double drive_time = 1;
   if(lower < 400){drive_time+=1;}
   PID_gyro_drive(400,drive_time);
   slow_servo(claw,claw_min+200,1);
   msleep(800);
   slow_servo(arm,arm_max,1);
   msleep(800);
   PID_gyro_drive(-500,2.5);
   turn_with_gyro(speed,0,0); 
   turn_with_gyro(speed,-90,0);
   Drive(-1300,-1*d_speed);
   square_up(2,-400);
   Drive(2350,d_speed);
   turn_with_gyro(speed,90,0);
   column_run();
}
void grab_rings(){
   //red orange yellow
    
   PID_gyro_drive(-200,1.8);
   slow_servo(arm, 1450,1); //1450
   PID_gyro_drive(200,2.2); 
   slow_servo(claw,claw_min+100,1);
   PID_gyro_drive(-500,1.5);
   reset_timer(3);
   square_up(2,-400);
   Drive(-2670,-50); //9.5625 inches 2670
   move(0,0);
   msleep(600);
   slow_servo(arm,arm_max,1);
   Drive(500,40);
   msleep(500);
   turn_with_gyro(550,90,1); 
   //push square up
   Drive(3000,50);
   square_up(2,400);
   Drive(-1300,-50);
   turn_with_gyro(550,180,0);
   column_run();
   
   ring_loop(400);
   ring_loop(250);
   /*
   thread_starting_pos();
   Drive(800,50);
   turn_with_gyro(550,-45,0);
   Drive(2200,50);
   turn_with_gyro(550,45,0);
   turn_with_gyro(550,90,0);
   */
   slow_servo(shifter,shifter_ver,1);
   slow_servo(arm,arm_min-300,1); 
   Drive(1500,50);
   turn_with_gyro(550,1,0); 
   Drive(1800,50);
   slow_servo(claw,claw_min,1);
   msleep(800);
   PID_gyro_drive(-500,4.5);
   turn_with_gyro(500,0,0);
   turn_with_gyro(500,45,0);
   PID_gyro_drive(500,4);
   turn_with_gyro(500,45,0);
    
   return ring_stand_return();
}
void ring_stand_return(){
    int ET=5;
    if(analog(ET)>2000){
    	turn_with_gyro(500,90,1);
        turn_with_gyro(500,-90,1);
    }
    if(analog(ET)<770){
        turn_with_gyro(500,-90,1);
        turn_with_gyro(500,90,1);
    }
    square_up(2,500); 
    if(analog(ET)<2000&&analog(ET)>1600){
    	turn_with_gyro(500,-22,1);
        drive_with_gyro(450,7);
    }
    if(analog(ET)<1600&&analog(ET)>1100){
    	turn_with_gyro(500,-30,1);
        drive_with_gyro(450,6.5);
    }
    if(analog(ET)<1100&&analog(ET)>900){
    	turn_with_gyro(500,-40,1);
        drive_with_gyro(450,7.5);
    }
}

/*
red: 3 
orange: 3 5/8
yellow: 3 7/8
green: 4 1/8
blue: 4 4/8
*/