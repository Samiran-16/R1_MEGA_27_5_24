#ifndef BLDC_H
#define BLDC_H

// #define ROTOR_DEBUG


void countPulse() {
  if (digitalRead(bldc_encoder) == LOW) {
    pulseCount++;
  }
}


bool rotor_start() {
#ifdef ROTOR_DEBUG
  Serial.println("rotar start");
#endif

  currentTime = millis();
  if (currentTime - lastTime >= interval) {  // PID Sampling
    rpmM2 = ((pulseCount * 60000) / 52000);
    pulseCount = 0;
    lastTime = currentTime;
    // Serial.print(rpmM2);
  }
  bldc_error = setpoint - rpmM2;
  bldc_pwm = bldc_base + ((bldc_error * kp) - (kd * (bldc_error - error_previous2)));
  error_previous2 = bldc_error;
  bldc_pwm = constrain(bldc_pwm, 0, 255);
  analogWrite(pwmM, bldc_pwm);
  // Serial.print("   ");
  // Serial.print("rpm  ");
  Serial.print(rpmM2);
  // // Serial.print(setpoint);
  // Serial.print("   ");
  // Serial.print(bldc_pwm);
  // bldc_base=bldc_pwm;
  // Serial.print(" BNO ");
  // Serial.print(yaw);
}
void rotor_onoff() {

  if (cmd == 'E') {
    if (BLDC_ON_Flag == false) {
      BLDC_ON_Flag = true;
    } else {
      BLDC_ON_Flag = false;
    }
  }
  cmd = NULL;

  if (BLDC_ON_Flag == true) {
    rotor_start();
  } else if (BLDC_ON_Flag == false) {
    setpoint = 0;
    bldc_base = 0;
    bldc_pwm = 0;
  }
}
void delay_(unsigned long time) {
  //to be changed
  unsigned long x = millis();
  while (millis() - x <= time) {
    rotor_start();
  }
}
void shoot_servo() {
  // analogWrite(servo, pick_pos[6]);
  // delay_(400);
  analogWrite(servo, pick_pos[2]);
  delay_(1500);
  analogWrite(servo, pick_pos[5]);
  delay_(100);
  analogWrite(grip_servo, grip_pos[5]);
}
bool shoot() {
  if (stepper_align_counter == 0) align_stepper(step_align[0]);
  else if (stepper_align_counter == 1) align_stepper(step_align[1]);
  else if (stepper_align_counter == 2) align_stepper_(step_align[2]);
  shoot_servo();
  if (stepper_align_counter == 0) align_stepper(-(step_align[0]));
  else if (stepper_align_counter == 1) align_stepper(-(step_align[1]));
  else if (stepper_align_counter == 2) align_stepper_(-(step_align[2]));
// alignToChassis(-90);
  // returnTo0();
}
void grip()

{
  if (flag_newgrip == 0) {
    analogWrite(servo, pick_pos[4]);
    delay_(500);
    analogWrite(grip_servo, grip_pos[2]);
    delay_(300);

    flag_newgrip = 1;
  } else if (flag_newgrip == 1) {
    analogWrite(servo, pick_pos[0]);
    delay_(100);
    analogWrite(grip_servo, grip_pos[1]);
    delay_(300);
    analogWrite(servo, pick_pos[1]);
    delay_(150);
    analogWrite(grip_servo, grip_pos[0]);
    delay_(350);
  
    analogWrite(servo, pick_pos[3]);
    delay_(150);
    flag_newgrip = 0;
    // shoot();
  }
}


void unfeed_for_servo() {
  analogWrite(servo, 240);
  delay_(300);
  // analogWrite(servo, 0);//////
  analogWrite(grip_servo, 145);
}



#endif