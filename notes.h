************AREA 2 TESTINGS************************

1]   180 32degree angle and -13 and 3000rpm with 220 Base
2]   66 12degree angle and 0 and 2500rpm with 200 Base
3]   15+10 FOR STAGE 2


FOR STEPPER WHEN COOOOOL

//                 Grip Ungrip
int grip_pos[2] = { 190, 125 };
//                    slow  med   fast
int bldc_speed[4] = { 2400, 2500, 3000, 1000 };
//                     slow   Med     Fast   First_180   Second_180 
int step_align[5] = { -24,     66,    180 ,    1060,        1004};
int bldc_b[3] =     { 190,    200,    220 };



FOR STEPPER WHEN HOT

int grip_pos[2] = { 190, 125 };
//                    slow  med   fast
int bldc_speed[4] = { 2400, 2500, 3000, 1000 };
//                     slow   Med     Fast   First_180   Second_180 
int step_align[5] = { -24,     66,    180 ,    1060,        1004};
int bldc_b[3] =     { 190,    200,    220 };


