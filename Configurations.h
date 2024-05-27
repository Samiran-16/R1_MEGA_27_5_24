#ifndef CONFIGURATION_H
#define CONFIGURATION_H

bool rotor_start();
bool pn_retract(bool, bool, bool, bool);
bool pn_extract(bool, bool, bool, bool);
bool pn_down(bool, bool);
bool pn_up(bool, bool);
void delay_(unsigned long time);

bool solenoid_init() {
  delay(350);
  digitalWrite(Solenoid_1, 1);
  digitalWrite(Solenoid_2, 1);
  delay(230);
  digitalWrite(Solenoid_1, 0);
  digitalWrite(Solenoid_2, 0);
}
bool init_setup() {
  //PNEUmatics all RETRACT
  //pn_Retract should be called HERE?//////////////////////////////
  pn_retract(1, 1, 1, 1);
  pn_down(1, 1);
  // analogWrite(servo, pick_pos[3]);

  // analogWrite(grip_servo, grip_pos[1]);
    analogWrite(servo, 80);

  analogWrite(grip_servo, 220);
}
bool setup_all() {
  // SERIAL COMMUNICATION //
  Serial.begin(38400);
  Serial2.begin(38400);
 Serial3.begin(38400);
  // Interrupt_ENCODER_ROTOR //


  //  TIP_LEFT
  pinMode(reset_pin,INPUT_PULLUP);
  pinMode(E13_L, OUTPUT);
  pinMode(R13_L, OUTPUT);
  pinMode(UP_L, OUTPUT);
  pinMode(DOWN_L, OUTPUT);
  pinMode(E24_L, OUTPUT);
  pinMode(R24_L, OUTPUT);
  //  TIP_RIGHT
  pinMode(E13_R, OUTPUT);
  pinMode(R13_R, OUTPUT);
  pinMode(UP_R, OUTPUT);
  pinMode(DOWN_R, OUTPUT);
  pinMode(E24_R, OUTPUT);
  pinMode(R24_R, OUTPUT);

  //SOLENOID 1
  pinMode(Solenoid_1, OUTPUT);
  //SOLENOID 2
  pinMode(Solenoid_2, OUTPUT);

  //  STEPPER //
  stepper.setMaxSpeed(20000.0);
  stepper.setAcceleration(700.0);
  stepper.setCurrentPosition(0);
  // stepper.setMinPulseWidth()

  //   BNO  //
  bno.begin();
  //  BLDC  //
  pinMode(bldc_encoder, INPUT_PULLUP);
  pinMode(grip_servo, OUTPUT);
  pinMode(ungrip, OUTPUT);
  pinMode(bldc_pwm, OUTPUT);
  pinMode(servo, OUTPUT);

  pinMode(proximity, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void stop_Act() {
  analogWrite(pwmM, 0);
  stepper.setSpeed(0);
}

void Stop() {
  stepper.setSpeed(0);
  // returnTo0();
  // alignToChassis(-90);
  if (BLDC_ON_Flag == true) {
    rotor_start();
  } else if (BLDC_ON_Flag == false) {
    setpoint = 0;
    bldc_base = 0;
    bldc_pwm = 0;
     rotor_start();
  }
}
#endif