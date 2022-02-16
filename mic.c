#include <kipr/wombat.h>
#include <mobility.h>
//yeet
thread srvo_cntrl;
int setup(){
    smart_servo(snow_hand,100,1.5,0);
    smart_servo(snow_arm,0,1.5,0);
    //smart_servo(3,100,1.5,0);
    srvo_cntrl = thread_create(servo_control);
    thread_start(srvo_cntrl);
    printf("Create.\n");
    create_connect();
    printf("--CREATE--\n\nBatt: %d\n\n-CONNECTED-\n",100*get_create_battery_charge()/get_create_battery_capacity());
    //snow_arm(0);
    //snow_hand(80);
    msleep(100);
    return(1);
}

void shutdown(){
    thread_destroy(srvo_cntrl);
    msleep(100);
    create_stop();
    msleep(50);
    create_disconnect();
}
