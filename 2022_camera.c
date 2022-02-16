#include </home/root/Documents/KISS/Default User/palms/include/functions.h>
#include </home/root/Documents/KISS/Default User/palms/include/variables.h>
#include <kipr/wombat.h>
//variables
servo_L=200;
servo_R=1800;
left=0;
right=1;
whiteL=183;
blackL=3665;
whiteR=165;
blackR=3243;
car=0.65;
int PercentReturns= (NumOfRepeats/3);
//NumOfRepeats=70;
int return_color(){
    //made by Noah F. Hicks.
    //it takes  seconds. It outputs 0 for green, 1 for blue, or 2 for unknown.
    counter=1;
    green_repeats=0;
	blue_repeats=0;
    camera_open_black();
    while (1){
        camera_update();
        if(get_object_count(0)>1&&get_object_confidence(0,0)>=car/*&&get_object_area(0,0)>300*/&&get_object_area(0,0)>get_object_area(1,0)){
            //printf("green\n");
            //printf("%d \n",get_object_area(0,0));
            green_repeats=green_repeats+1;
        } 
        else if(get_object_count(1)>1&&get_object_confidence(1,0)>=car/*&&get_object_area(1,0)>300*/&&get_object_area(0,0)<get_object_area(1,0)){
            //printf("blue\n");
            //printf("%d \n",get_object_area(1,0));
            blue_repeats=blue_repeats+1;
        }
        if(counter==NumOfRepeats){break;}counter=counter+1;
    }
    printf("%d\n", green_repeats);
    printf("%d\n", blue_repeats);
    if(blue_repeats>=PercentReturns||blue_repeats>green_repeats+5){
    	//printf("blue\n");
        return(1);
    }else if(green_repeats>=PercentReturns||green_repeats>blue_repeats+5){
    	//printf("green\n");
        return(0);
    }
    
	return(2);    
}
void motor_freeze(){
	motor(left_motor,0);
    motor(right_motor,0);
    msleep(10);
}
void move_to_object(channel){
    camera_update();camera_update();camera_update();camera_update();camera_update();camera_update();
	while(1){
        camera_update();
        printf("in loop\n");
        printf("%d",get_object_center_y(channel,0));
    	if(get_object_center_y(channel,0)>95||get_object_count(channel)<1){
        	motor(0,0);
			motor(3,0);
    		msleep(50);
            printf("break\n");
            break;
        }
        
        printf("moving forward\n");
        move(500,500);
        
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//int right_motor = 0;
//int left_motor = 3;
int speed = 750;
//int whiteL=183;
//int blackL=3665;
//int whiteR=165;
//int blackR=3243;
void perfecturn(int direction){
// 1 for a 90 degrees turn to forward left
// 2 for a 90 degrees turn to forward right
// 3 for a 90 degress turn to backward left
// 4 for a 90 degrees turn to backward right
	if(direction == 1){
		mav(right_motor, speed);
		msleep(flturn);
        motor_freeze();
    }
	if(direction == 2){
		mav(left_motor, speed);
		msleep(frturn);
    	motor_freeze();
    }
	if(direction == 3){
		mav(right_motor, -speed);
		msleep(blturn);
    	motor_freeze();
    }
	else if(direction == 4){
		mav(left_motor, -speed);
		msleep(brturn);
    	motor_freeze();
    }
	motor(0,0);
	motor(3,0);
    msleep(50);
}

void sort(){
    color=2;
    while(color=2){
        printf("sorting\n");
        color=return_color();
        servo(0, semiddle, 3);
        //position_camera(color);
            if(color == 0)
			{
				printf("Moving Green");
                servo(0, seleft, 3);
                move_to_object(0);
				motor_freeze();
                servo(0, seright, 4);
				break;
            }
        	if(color == 1)
			{
				printf("Moving Blue");
                servo(0, seright, 3);
                move_to_object(1);
				motor_freeze();
                servo(0, seleft, 4);
				break;
            }
    }
}

void psquare_up(time){
    move(-100,-100);
    msleep(time);
	motor_freeze();
}
