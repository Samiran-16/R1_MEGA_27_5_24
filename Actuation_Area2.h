#ifndef ACTUATION_AREA2_H
#define ACTUATION_AREA2_H

bool detect_ball() {
  if (digitalRead(proximity) == 0) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
bool grip_ball() {
  analogWrite(grip_servo, grip_pos[0]);
  unsigned long w = millis();
  while (millis() - w <= 300) {
    analogWrite(servo, pick_pos[1]);
  }
}

// bool shoot() {
//    if(stepper_align_counter==0)align_stepper(step_align[0]);
//    else if(stepper_align_counter==1)align_stepper(step_align[1]);
//    else if(stepper_align_counter==2)align_stepper_(step_align[2]);
//    shoot_servo();
//    if(stepper_align_counter==0)align_stepper(-(step_align[0]));
//    else if(stepper_align_counter==1)align_stepper(-(step_align[1]+7));
//    else if(stepper_align_counter==2)align_stepper_(-(step_align[2]+13));


// }


void change_rpm() {
  
  if (cmd == 'd') setpoint = bldc_speed[0], bldc_base = bldc_b[0], stepper_align_counter = 0;
  else if (cmd == 'g') setpoint = bldc_speed[1], bldc_base = bldc_b[1], stepper_align_counter = 1;
  else if (cmd == 'e') setpoint = bldc_speed[2], bldc_base = bldc_b[2], stepper_align_counter = 2;
  else setpoint = bldc_speed[0], bldc_base = bldc_b[0];
}
void area_switch() {
  // BLDC_ON_Flag = true;
  pn_retract(1, 1, 1, 1);
  pn_up(1, 1);
  // anti_rotate_90();
  // cmd = 'e';
  // change_rpm();
  cmd = 's';
}
void slope_detect() {
  if (slope > 4) {
      pn_retract(1, 1, 1, 1);
  pn_up(1, 1);
    BLDC_ON_Flag = true;
    cmd = 'e';
    change_rpm();
    cmd = 's';
  } else {
    cmd = 's';
  }
}
#endif