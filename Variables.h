
#include <Servo.h>
#include "String.h"
#include "Wire.h"
#include <MPU6050_light.h>
#include <AccelStepper.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <ArduinoJson.h>
#include <String.h>
#include <stdio.h>

#ifndef VARIABLES_H
#define VARIABLES_H


//  Pneumatics
//In Use Pins: 39 41 43 45 47 49  \/ 23 25 27 29 31 33 \/ 42 44 9 11 34 6
//LEFT
#define delay_pn 500
#define E13_L 27   //e13L
#define R13_L 29   //r13L
#define UP_L 23    // lup
#define DOWN_L 25  //ld
#define E24_L 31   //e24L
#define R24_L 33   //r24L
//RIGHTq
#define E13_R 41  //e13r
#define R13_R 43  //r13r
#define UP_R 44   //rup
#define DOWN_R 9  //rd
#define E24_R 39  //e24r
#define R24_R 45  //r24r

#define Solenoid_1 6
#define Solenoid_2 47
//STEPPER
#define STEP_PIN 3
#define DIR_PIN 40

//  BLDC
#define bldc_encoder 19
// #define grip_servo 25
#define ungrip 31
#define servo 7
#define grip_servo 8
#define pwmM 2

#define proximity A4
#define led A3

#define BUFFER_SIZE 5
#define reset_pin 4
char receivedData[BUFFER_SIZE + 1];
//STRING
String command;
char cmd = 'S';


//Stepper
int flag_step = 0;
int yaw = 0;
double error_step = 0;
double setpoint_step = 0;
double total_step = 0;
double prev_step = 0;

/////
int temp_yaw = 0;
int slope = 0;
int bno_change = 0;
char bno_char;
int bno_chassis = 0;
int new_setpoint = 0;
///
AccelStepper stepper(1, STEP_PIN, DIR_PIN);
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
unsigned long timer_step = 0;
int step_constant[3] = { 5.44, 6.23, 6.34 };
// MPU6050 mpu(Wire);

//BLDC
//variables for rpm
unsigned long currentTime = 0;
unsigned long lastTime = 0;
volatile unsigned long rpmM2;
unsigned long pulseCount = 0;
const unsigned long interval = 85;
unsigned long delay_millis = 0;
int setpoint_flag = 0;
bool flag_90 = false;
//variables for feed
bool BLDC_ON_Flag = false;
int flag_unfeed = 2;
int flag_grip = 1;
volatile int bldc_pwm;

int setpoint = 3000;
volatile int bldc_base = 230;
volatile int bldc_error = 0;
const float kp = 0.05;
const float kd = 0.1;
volatile int error_previous2 = 0;

//Servo
Servo servo_claw;
Servo servo_arm;


//FLAGS

//PNEUMATICS
bool flag_Pneumatics = true;
bool flag_Pneumatics1 = true;
bool flag_Pneumatics2 = true;
bool flag_Pneumatics3 = true;
bool flag_Pneumatics4 = true;
bool flag_Pneumatics5 = true;
bool flag_Pneumatics6 = true;
bool toggle = false;
bool toggle_pfr = false;
// bool toggle_pfr2=false;
// bool toggle_pfr3=false;
bool flag_L13 = true;
bool flag_R13 = true;
bool flag_L24 = true;
bool flag_R24 = true;
bool flag_Lud = true;
bool flag_Rud = true;
bool step_pneumatics = false;
int cnt_pickseed = 0;
//////////////////////////////////////BNO
int prev_val = 0;
int counter = 0;
int z = 0;
long timer_bno = 0;
//////////////////
int place_counter = 0;
bool time_flag = true;
int stepper_align_counter = 0;
int start_flag = 0;
bool flag_newgrip = 0;
int setpt = 0;


/*XXXXXXXXXXXXXXXXXXX  VARIABLES  XXXXXXXXXXXXXXXXXXXXX*/
//                 Down  pick feed standby
int pick_pos[7] = { 240, 235, 59, 175, 165, 139, 86 };  //Order of setpoints are according to the steps of actuations
//                 Grip   fullug   First after_shoot
int grip_pos[4] = { 227, 150, 150, 165 };
//                    slow  med   fast
int bldc_speed[4] = { 2900, 2900, 3200, 1000 };
//                     slow   Med     Fast   First_180   Second_180
int step_align[5] = { -40, -100, -180, 1020, 1050 };

// int step_align[5] = { -24,     66,    180 ,    2106,        2046};
int bldc_b[3] = { 180, 180, 230 };
////180 32degree angle and -13 and 3000rpm with 220 Base
//// 66 12degree angle and 0 and 2500rpm with 200 Base
////-24
//json
// String esp_data = " ";
DynamicJsonDocument doc(200);
DynamicJsonDocument docbno(256);


char c[4] = { NULL, NULL, NULL, NULL };
String json = "";
String jsonbno = "";

DeserializationError Jsonerrorbno;
DeserializationError Jsonerror;
#endif