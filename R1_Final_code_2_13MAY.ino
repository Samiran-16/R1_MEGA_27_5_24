#include "Variables.h"
#include "BNO.h"
#include "Configurations.h"
#include "Stepper.h"
#include "BLDC.h"
#include "Pneumatics.h"

#include "Actuation_Area1.h"
#include "Actuation_Area2.h"

#include "json.h"

void setup() {
  setup_all();
  init_setup();
  attachInterrupt(digitalPinToInterrupt(bldc_encoder), countPulse, CHANGE);
  delay(500);
}

void loop() {
  json_rec();
  // bno_CHASSIS();
  bno_val();
  Serial.print(bno_chassis);
  Serial.print("  :  ");
  Serial.print(yaw);
  Serial.println(cmd);
  _switch(cmd);
}

void _switch(char C) {
  switch (C) {
    // AREA_1     START //////////////////////////////////////
    //Seedling Pick
    //x to Y
    case 'Y':
      if (!pick_seed()) cmd = 'Y';
      else cmd = 'S';

      break;
    case 'X':
      start_flag++;
      if (start_flag == 9) {
        break;
      } else if (start_flag == 1) {
        setpt = 0;
        start();
      } else if (start_flag == 2) {
        // alignToSet(180);
        rotate_180();

        setpt = 180;
        // bno_CHASSIS();
        // bno_val();
        // delay(150);
        // alignToChassis(setpt);
        // step_pneumatics = 1;
        cmd = 'S';
      } else if (start_flag == 3) {
        // delay(500);
        // Serial.print("Step");
        delay(1900);
        stepper.setMaxSpeed(3000);
        stepper.setAcceleration(0);
        // anti_rotate_90();
        alignToSet(89);
        setpt = 88;
        // bno_CHASSIS();
        // bno_val();
        // delay(150);

        // alignToChassis(setpt);
        // alignToChassis();
        cmd = 'S';
      } else if (start_flag == 4) {
        cmd = 'S';
      } else if (start_flag == 5) {
        delay(420);
        stepper.setMaxSpeed(2500);
        stepper.setAcceleration(0);
        flag_90 = true;
        alignToSet(-85);
        setpt = -89;
        // bno_CHASSIS();
        // bno_val();
        // delay(150);
        // alignToChassis(setpt);
        // alignToChassis();
        // anti_rotate_180_new();
        flag_90 = false;
        step_pneumatics = 0;
        cmd = 'S';
      } else if (start_flag == 6) {
        // rotate_180();
        cmd = 'S';
      } else if (start_flag == 7) {
        // delay(2500);

        delay(1300);
        alignToSet(0);
        // rotate_90();
        // setpt = 90;
        // bno_CHASSIS();
        // bno_val();
        // delay(150)
        // delay(1000);
        // alignToChassis(setpt);

        // alignToChassis();
        cmd = 'S';
      } else if (start_flag == 8) {
        // alignToSet(-90);
        delay(2600);
        anti_rotate_90();
        setpt = 90;
        // bno_CHASSIS();
        // bno_val();
        // delay(150);
        // delay(1000);
        // alignToChassis(setpt);
        cmd = 'S';
      }
      break;
      //Seedling Place
    case 'B':
      if (!place_seed()) cmd = 'B';
      else cmd = 'S';
      break;
    case 'D':
      pn_extract(1, 1, 1, 1);
      break;
      //Stepper Rotation
    // case 'T':
    //   rotate_180(), cmd = 'T';
    //   break;
    /////////////////////  AREA_1     END ////////////////////////
    case 'w':
      // c[0]='E';
      // if (BLDC_ON_Flag == false) {
      //   BLDC_ON_Flag = true;
      // } else {
      BLDC_ON_Flag = false;
      change_rpm();
      Stop();
      // }
      break;

    case 'J':
      grip();

      // alignToChassis(setpt);
      break;

    case 'O':
      rotate_manual();
      break;

    case 'o':
      anti_rotate_manual();
      break;

    case 'A':
      shoot();
      break;

    case 'd':
      BLDC_ON_Flag = true;
      change_rpm();
      break;
    case 'g':
      BLDC_ON_Flag = true;
      change_rpm();
      break;
    case 'e':
      BLDC_ON_Flag = true;
      change_rpm();
      break;

    case 'S':
      Stop();
      break;

    case 'i':
      anti_rotate_90();
      break;
    case 'I':
      rotate_90man();
      break;
    case 'P':
      pfr_13();
      // alignToChassis();
      break;
    case 'p':
      pfr_24();
      // alignToSet(-30);

      break;
    case 'C':
      pfr_ud();
      break;
    case 'c':
      //RIGHT
      toggle_pfr = true;
      delay(400);
      break;
    case 'j':
      //LEFT
      toggle_pfr = false;
      delay(400);
      break;
    case 'v':
      area_switch();
      break;
    //   case 'p':
    //  resetFunc();
    //   break;
    case 's':
      Stop();
      break;
    default:
      Stop();
      break;
  }
}