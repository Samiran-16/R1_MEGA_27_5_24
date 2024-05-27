#ifndef STEPPER_H
#define STEPPER_H
int align = 0;
int n_align = 0;
bool rotate_180() {
  if (step_pneumatics == 0) {
    // bno_val();
    // if ((yaw * setpoint_step) < 0 && setpoint_step > 0) counter = -1;
    // else if ((yaw * setpoint_step) < 0 && setpoint_step < 0) counter = 0;
    counter = -1;
    prev_step = 1020;
    stepper.setMaxSpeed(2000);

    stepper.setAcceleration(490.0);
    stepper.moveTo((step_align[3]));

    //1010
    while (stepper.isRunning()) {
      stepper.run();
    }
    // // alignToSet(-180);
    bno_val();
    // alignToChassis();

    step_pneumatics = 1;
  } else if (step_pneumatics == 1) {
    stepper.setMaxSpeed(450);
    stepper.setAcceleration(650.0);
    stepper.setCurrentPosition(0);
    delay(670);
    stepper.moveTo(-step_align[4]);
    while (stepper.isRunning()) {
      stepper.run();
      // alignToChassis();
    }
    // alignTo0();
    // returnTo0();
    step_pneumatics = 0;
  } else if (step_pneumatics == 2) {
    stepper.setAcceleration(400.0);
    stepper.moveTo(1010);
    //1010
    while (stepper.isRunning()) {
      stepper.run();
    }
    step_pneumatics = 3;
  } else if (step_pneumatics == 3) {
    stepper.setAcceleration(700.0);
    stepper.moveTo(0);
    while (stepper.isRunning()) {
      stepper.run();
    }
    step_pneumatics = 2;
  }
}
bool rotate_90() {
  counter = -1;
  prev_step = 0;
  stepper.setMaxSpeed(400);
  stepper.setAcceleration(0);
  stepper.moveTo(stepper.currentPosition() + 511);
  while (stepper.isRunning()) {
    stepper.run();
  }
}

bool rotate_90man() {
  // counter = -1;
  // prev_step = 0;
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(0);
  stepper.moveTo(stepper.currentPosition() + 511);
  while (stepper.isRunning()) {
    stepper.run();
  }
}
bool rotate_manual() {

  stepper.setMaxSpeed(2000.0);
  stepper.setAcceleration(700.0);
  prev_step = stepper.currentPosition() + 20;
  align = stepper.currentPosition() + 20;
  stepper.moveTo(align);
  while (stepper.isRunning()) {
    stepper.run();
  }
}

bool anti_rotate_manual() {
  stepper.setMaxSpeed(2000.0);
  stepper.setAcceleration(700.0);
  prev_step = stepper.currentPosition() - 20;
  n_align = stepper.currentPosition() - 20;
  stepper.moveTo(n_align);
  while (stepper.isRunning()) {
    stepper.run();
  }
}

bool anti_rotate_90() {
  stepper.setMaxSpeed(3000);
  stepper.setAcceleration(0);
  stepper.moveTo(stepper.currentPosition() - 512);
  while (stepper.isRunning()) {
    stepper.run();
  }
}
void align_stepper(int setpoint) {

  stepper.setAcceleration(0.0);
  setpoint += stepper.currentPosition();
  stepper.moveTo(setpoint);
  while (stepper.isRunning()) {
    stepper.run();
  }
}
void align_stepper_(int setpoint) {
  stepper.setAcceleration(0.0);
  setpoint += stepper.currentPosition();
  stepper.moveTo(setpoint);
  while (stepper.isRunning()) {
    stepper.run();
  }
}

bool anti_rotate_180_new() {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(650.0);
  stepper.moveTo(stepper.currentPosition() - 1040);
  while (stepper.isRunning()) {
    stepper.run();
  }
  step_pneumatics = 0;
}
bool rotate_180_new() {
  stepper.setMaxSpeed(3000);
  stepper.setAcceleration(0);
  stepper.moveTo(stepper.currentPosition() + 1022);
  while (stepper.isRunning()) {
    stepper.run();
  }
}
#endif