#ifndef BNO_H
#define BNO_H

#define BNO_VAL
#define BNO_CHASSIS

#ifdef BNO_CHASSIS
void bno_CHASSIS() {
  if (Serial3.available() > 0) {
    jsonbno = Serial3.readStringUntil('*');

    Jsonerrorbno = deserializeJson(docbno, jsonbno);
    if (Jsonerrorbno) {
      // Serial.println(Jsonerror.f_str());
      return;
    } else {
      if (docbno["yaw"] != nullptr) bno_chassis = docbno["yaw"];
    }
  }
  delay(10);
}
#endif

#ifdef BNO_VAL
void bno_val() {
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  sensors_event_t* event = &orientationData;
  if ((millis() - timer_bno) > 10) {
    z = event->orientation.x;

    if (z - prev_val <= -300) counter++;
    else if (z - prev_val >= 300) counter--;
    // yaw2 = (z % 360) + 360 * counter;
    // yaw = abs((z % 360) + 360 * counter);
    yaw = (z % 360) + 360 * counter;

    prev_val = z;
    timer_bno = millis();
    // prev_val = z;

    // yaw = abs(yaw);
  }
  yaw = -yaw;
  delay(10);
}

#endif
void returnTo0() {
  stepper.setAcceleration(0);
  stepper.setMaxSpeed(3000);
  while (!(yaw > -2 && yaw < 2)) {
    // error_step = yaw - setpoint_step;
    error_step = 0 - yaw;
    total_step = 0;
    total_step = (error_step * (5.4));

    total_step += prev_step;
    prev_step = total_step;

    //                   +VE ----> CLK
    //                   -VE ----> AntiCLK
    //FOR STM
    //                  +VE---> AntiCLK
    //                  -VE---> CLK
    stepper.moveTo(total_step);
    while (stepper.isRunning()) {
      stepper.run();
    }
    bno_val();
  }
}

void alignToSet(int setpoint_step) {
  bno_val();
  // bno_val();
  if ((yaw * setpoint_step) < 0 && setpoint_step > 0) counter = -1;
  else if ((yaw * setpoint_step) < 0 && setpoint_step < 0) counter = 0;

  while (!(yaw > setpoint_step - 2 && yaw < setpoint_step + 2)) {
    error_step = setpoint_step - yaw;
    Serial.print("error step is :");
    Serial.println(error_step);
    if (error_step < 5 && error_step > -5) { stepper.setMaxSpeed(100); }
    total_step = 0;
    if (flag_90 == true) {
      total_step = (error_step * (step_constant[1]));
    } else {
      total_step = (error_step * (step_constant[0]));
    }
    total_step += prev_step;
    prev_step = total_step;
    // Serial.print(total_step);
    //                   +VE ----> CLK
    //                   -VE ----> AntiCLK
    //FOR STM
    //                  +VE---> AntiCLK
    //                  -VE---> CLK
    Serial.print(yaw);
    Serial.print(" : ");
    Serial.print(z);
    Serial.print(" : ");
    Serial.print(prev_val);
    Serial.print(" : ");
    Serial.println(counter);
    // Serial.print(total_step);
    stepper.moveTo(total_step);
    while (stepper.isRunning()) {
      stepper.run();
    }

    bno_val();
  }
}
// void alignToSet(int setpoint_step) {
//  bno_val();
//   while (!(yaw > (setpoint_step - 4) && yaw < (setpoint_step + 4))) {
//      bno_val();
//     error_step = setpoint_step - yaw;

//     total_step = 0;
//     total_step = (error_step * (5.1));

//     total_step += prev_step;
//     prev_step = total_step;
//     if (alignSet_flag == false) {
//       total_step += stepper.currentPosition();
//       alignSet_flag = true;
//     }
//     Serial.print("  YAW");
//     Serial.print(yaw);
//     Serial.print("  Insude");
//     Serial.print(total_step);
//     stepper.moveTo(total_step);
//     while (stepper.isRunning()) {
//       stepper.run();
//     }
//    stepper.setMaxSpeed(500);
//     Serial.print("Insude");
//     Serial.println(total_step);
//       prev_step = 0;
//   alignSet_flag = false;
//   }

// }

void alignToChassis(int align_constant) {
  bno_CHASSIS();
  bno_val();
  stepper.setMaxSpeed(2500);
  stepper.setAcceleration(0);
  // yaw -= 10;
  
  bno_change = (yaw - bno_chassis) * step_constant[2] - align_constant*step_constant[2];
  Serial.println("bno_change: " + String(bno_change));
  prev_step = stepper.currentPosition() - bno_change;
  // Serial.println("bno_change: " + String(bno_change));
  stepper.moveTo(stepper.currentPosition() - bno_change);
    Serial.print(stepper.currentPosition());
  while (stepper.isRunning()) {
    stepper.run();
  }
  Serial.print(" IN :");
  Serial.print(stepper.currentPosition());
  Serial.print(" CHANGE :");
  Serial.print(bno_change);
}

// void alignToChassis_90() {
//   bno_CHASSIS();
//   bno_val();
//   stepper.setMaxSpeed(2500);
//   stepper.setAcceleration(0);
//   yaw -= 5;
//   bno_change = (yaw - bno_chassis) * step_constant[2] + 90 * step_constant[0];
//   Serial.println("bno_change: " + String(bno_change));
//   prev_step = stepper.currentPosition() + bno_change;
//   // Serial.println("bno_change: " + String(bno_change));
//   stepper.moveTo(stepper.currentPosition() - bno_change);
//   while (stepper.isRunning()) {
//     stepper.run();
//   }
// }
// void alignToChassis_180() {
//   bno_CHASSIS();
//   bno_val();
//   stepper.setMaxSpeed(2500);
//   stepper.setAcceleration(0);
//   yaw -= 5;
//   bno_change = (yaw - bno_chassis) * step_constant[2] + 180 * step_constant[0];
//   Serial.println("bno_change: " + String(bno_change));
//   prev_step = stepper.currentPosition() + bno_change;
//   // Serial.println("bno_change: " + String(bno_change));
//   stepper.moveTo(stepper.currentPosition() - bno_change);
//   while (stepper.isRunning()) {
//     stepper.run();
//   }
// }

// void alignToChassis_NOT_90() {
//   bno_CHASSIS();
//   bno_val();
//   stepper.setMaxSpeed(2500);
//   stepper.setAcceleration(0);
//   yaw -= 5;
//   bno_change = (yaw - bno_chassis) * step_constant[2] - 90 * step_constant[0];
//   Serial.println("bno_change: " + String(bno_change));
//   prev_step = stepper.currentPosition() + bno_change;
//   // Serial.println("bno_change: " + String(bno_change));
//   stepper.moveTo(stepper.currentPosition() - bno_change);
//   while (stepper.isRunning()) {
//     stepper.run();
//   }
// }
#endif