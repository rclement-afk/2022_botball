#include <kipr/wombat.h>
#include <mobility.h>
int servo_controls[4][4]={{0,50,1,0},{0,50,1,0},{0,100,1,0},{0,100,1,0}};
int accel(int speed){
    if(speed<75){create_drive_direct(speed,speed);return 0;}
    int m_speed,s_seconds=seconds();
    int per_sec=400;
    while((seconds()-s_seconds)*per_sec<speed){
        m_speed=(seconds()-s_seconds)*per_sec;
        create_drive_direct(m_speed,m_speed);
        msleep(15);
    }
    
    return 1;
}
int dccel(int speed){
    if(speed<75){create_drive_direct(0,0);return 0;}
	int per_sec=300,s_seconds=seconds();
    int m_speed=speed-((seconds()-s_seconds)*per_sec);
    while(m_speed>1){
        m_speed=speed-((seconds()-s_seconds)*per_sec);
        create_drive_direct(m_speed,m_speed);
        msleep(15);
    }
    create_drive_direct(0,0);
    return 1;
}
void motors(int L, int R){
    create_drive_direct(L,R);
}

int square_up(){
    int R,L,loops_bl=99;
    //reverse if on black
    if(get_create_lfcliff_amt()<1800 || get_create_rfcliff_amt()<1800){   
        while(get_create_lfcliff_amt()<1800 || get_create_rfcliff_amt()<1800){
            create_drive_direct(-100,-100);
            msleep(10);
        }msleep(200);}
    while(loops_bl>=4){//forward to black
        //square white if >1st time through
        if(loops_bl<90){
            //printf("black -> white\n");
            while(!(get_create_lfcliff_amt()>1800 && get_create_rfcliff_amt()>1800)){
                if(get_create_lfcliff_amt()<1800){L=square_up_speed*-1.5;}else{L=square_up_speed;}
                if(get_create_rfcliff_amt()<1800){R=square_up_speed*-1.5;}else{R=square_up_speed;}
                create_drive_direct(L,R);
                msleep(20);
            }
            //create_drive_direct(square_up_speed*-1,square_up_speed*-1);
            //msleep(100);
        }
        loops_bl=0;
        //square up black
        //printf("black\n");
        while(!(get_create_lfcliff_amt()<1800 && get_create_rfcliff_amt()<1800)){
            if(get_create_lfcliff_amt()>1800){L=square_up_speed;}else{L=square_up_speed*-1.5;loops_bl=loops_bl+1;}
            if(get_create_rfcliff_amt()>1800){R=square_up_speed;}else{R=square_up_speed*-1.5;loops_bl=loops_bl+1;}
            create_drive_direct(L,R);
            msleep(20);
        }
        //printf("%d\n",loops_bl);
    }
    create_drive_direct(0,0);
    return loops_bl;
}
void rotate(int deg){
    int fast=100;
    int speed,prev=0,theta=0;
    deg=deg*rotate_deg_factor;
    set_create_total_angle(0);
    while(theta>deg+1 || theta<deg-1){
        theta=get_create_total_angle();

        //total_angle sometimes glitches out and this saves it
        if(theta>prev+10 || theta<prev-10){set_create_total_angle(prev);printf("\n=_=\n");theta=get_create_total_angle();}

        prev=theta;
        speed=(10*(deg-theta))^4;
        if(speed> 	fast){speed=   fast;}
        if(speed<-1*fast){speed=-1*fast;}
        create_drive_direct(speed*-1,speed*1);
        msleep(15);
        //printf("%d ",theta);
    }
    printf("\n%d\n",(int)(get_create_total_angle()/rotate_deg_factor));
    motors(0,0);
}

void gyro_drive(int speed,float time,int end){
    int theta=0,prev=0;
    float startTime = seconds();
    set_create_total_angle(0);
    accel(speed);
    while(1){
        theta=get_create_total_angle();
        //total_angle sometimes glitches out and this saves it
        if(theta>prev+10 || theta<prev-10){set_create_total_angle(prev);printf("\n=_=\n");theta=get_create_total_angle();}
        prev=theta;
        create_drive_direct(speed+(theta*15),speed+(theta*-15));
        if(seconds()-startTime>time){break;}
        msleep(15);
    }
    if(end){dccel(speed);}
}
void smart_servo(int port, int perc, float time, int delay){
    servo_controls[port][0]=get_servo_position(port);
    //msleep(50);
    //printf("%d\n",(int)servo_controls[port]);
    servo_controls[port][1]=perc;
    servo_controls[port][2]=time*100;
    servo_controls[port][3]=seconds()+delay;
}

void servo_control(){
    // 						 |start pos|,|end pos|,|time|, |start time|
    float psi;
    //(seconds()-servo_controls[0][3])/(servo_controls[0][2]/100.0) 0-1
    //set servos before enable
    enable_servos();
    //int servo_positions[4]={1600,0,1000,1000};
    //set_servo_position(0,servo_positions[0]);set_servo_position(1,servo_positions[1]);set_servo_position(2,servo_positions[2]);set_servo_position(3,servo_positions[3]);
    msleep(100);
    while(1){
        if(seconds()-servo_controls[0][3]<=servo_controls[0][2]/100.0 && seconds()>servo_controls[0][3]){
            psi=servo_controls[0][0]+(((max_0-min_0)*(servo_controls[0][1]/100.0)+min_0)-servo_controls[0][0])*(seconds()-servo_controls[0][3])/(servo_controls[0][2]/100.0);
            set_servo_position(0,(int)psi);
            //printf("%f	",psi);
        }
        if(seconds()-servo_controls[2][3]<=servo_controls[2][2]/100.0 && seconds()>servo_controls[2][3]){
            psi=servo_controls[2][0]+(((max_2-min_2)*(servo_controls[2][1]/100.0)+min_2)-servo_controls[2][0])*(seconds()-servo_controls[2][3])/(servo_controls[2][2]/100.0);
            set_servo_position(2,(int)psi);
            //printf("%f	",psi);
        }
        /*if(seconds()-servo_controls[3][3]<=servo_controls[3][2]/100.0 && seconds()>servo_controls[3][3]){
            psi=servo_controls[3][0]+(((max_3-min_3)*(servo_controls[3][1]/100.0)+min_3)-servo_controls[3][0])*(seconds()-servo_controls[3][3])/(servo_controls[3][2]/100.0);
            set_servo_position(3,(int)psi);
            //printf("%f	",psi);
        }*/

        msleep(30);
    }
}
void line_follow(int speed,int side,float time)
{
    //int speed=50;
    int s_time=seconds(),mod;
    int cliff;
    if(max+100<get_create_lfcliff_amt() || min-100>get_create_lfcliff_amt())
    {max=get_create_lfcliff_amt(),min=get_create_lfcliff_amt()-200;}
	accel(speed);
    switch(side){
        case 2:
            printf("side:2\n");
            max=get_create_lfcliff_amt(),min=get_create_lfcliff_amt()-200;
            while(seconds()-s_time<time){
                cliff=get_create_lfcliff_amt();
                if(cliff>max){max=cliff;}
                if(cliff<min){min=cliff;}
                mod=(cliff-(max+min)/2)/((max-min)/100+5);
                create_drive_direct(speed-mod,speed+mod);
                msleep(15);
                printf("%d ",mod);

            }break;
        case 1:
            printf("side:1\n");
            max=get_create_lfcliff_amt(),min=get_create_lfcliff_amt()-200;
            while(seconds()-s_time<time){
                cliff=get_create_lfcliff_amt();
                if(cliff>max){max=cliff;}
                if(cliff<min){min=cliff;}
                mod=(cliff-(max+min)/2)/((max-min)/100+5);
                create_drive_direct(speed-mod,speed+mod);
                msleep(15);
                printf("%d ",mod);

            }break;
        case -1:
            printf("side:-1\n");
            max=get_create_lfcliff_amt(),min=get_create_lfcliff_amt()-200;
            while(seconds()-s_time<time){
                cliff=get_create_lfcliff_amt();
                if(cliff>max){max=cliff;}
                if(cliff<min){min=cliff;}
                mod=(cliff-(max+min)/2)/((max-min)/100+5);
                create_drive_direct(speed-mod,speed+mod);
                msleep(15);
                printf("%d ",mod);

            }break;
        case -2:
            printf("-2\n");

            while(seconds()-s_time<time){
                cliff=get_create_rfcliff_amt();
                if(cliff>max){max=cliff;}
                if(cliff<min){min=cliff;}
                mod=(cliff-(max+min)/2)/((max-min)/100+5);
                create_drive_direct(speed+mod,speed-mod);
                msleep(15);
                printf("%d ",mod);

            }break;
    }
    create_drive_direct(0,0);
    printf("\nMax: %d\nMin: %d\n\n",max,min);
}
