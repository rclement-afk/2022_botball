#define square_up_speed 150
#define rotate_deg_factor -1.16

#define snow_arm 2
#define snow_hand 0

#define max_0 1600
#define min_0 500
#define max_2 1800
#define min_2 700
#define max_3 0
#define min_3 0

int servo_positions[4];
int servo_controls[4][4];
int max,min;
 
int accel(int speed);
int dccel(int speed);
void motors(int L,int R);
int square_up();
void rotate(int deg);
void gyro_drive(int speed,float time,int end);
void servo_control();
void smart_servo(int port, int perc, float time, int delay);
void line_follow(int speed, int side, float time);

//servo positions
#define tenis_low_arm 78

