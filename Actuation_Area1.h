#ifndef ACTUATION_AREA1_H
#define ACTUATION_AREA1_H

bool start() {
  delay(350);
  digitalWrite(Solenoid_1, 1);
  digitalWrite(Solenoid_2, 1);
  delay(500);
  pn_extract(1, 1, 1, 1);
  pn_down(1, 1);

  digitalWrite(Solenoid_1, 0);
  digitalWrite(Solenoid_2, 0);
  start_flag = true;
}
bool pick_seed() {
  if (step_pneumatics == false) {
    if (cnt_pickseed == 0) {
      pn_retract(1, 1, 0, 0);
      delay(100);
      pn_up(1, 0);
      cnt_pickseed = 1;
    }
    //  else if (cnt_pickseed == 1) {
    //   pn_down(1, 0);
    //   pn_extract(1, 1, 0, 0);
    //   cnt_pickseed = 2;{
    else if (cnt_pickseed == 1) {
      pn_retract(1, 1, 0, 0);
      delay(100);
      pn_up(1, 0);
    }
  } else if (step_pneumatics == true) {
    pn_retract(0, 0, 1, 1);
    delay(100);
    pn_up(0, 1);
  }
  return true;
}
// bool place_seed() {
//   if (step_pneumatics == true) {

//     pn_down(0, 1);
//     delay(100);
//     /////place 13 and 24
//     if (place_counter == 0) pn_extract(0, 0, 1, 0), place_counter = 1;
//     else if (place_counter == 1) pn_extract(0, 0, 0, 1), place_counter = 2;
//     delay(100);
//     pn_up(0, 1);
//   }

bool place_seed() {
  if (step_pneumatics == true) {

    pn_down(0, 1);
    delay(100);
    /////place 13 and 24
    if (place_counter == 0) {
      place_counter = 1;
      return true;
    } else if (place_counter == 1) pn_extract(0, 0, 1, 0), place_counter = 2;
    else if (place_counter == 2) {
      place_counter = 3;
      return true;
    } else if (place_counter == 3) pn_extract(0, 0, 0, 1), place_counter = 4;
    delay(100);
    pn_up(0, 1);
  }


  if (step_pneumatics == false) {
    pn_down(1, 0);
    delay(100);
    /////place 13 and 24
    if (place_counter == 4) {
      place_counter = 5;
      return true;
    } else if (place_counter == 5) {
      pn_extract(1, 0, 0, 0), place_counter = 6;
      // return true;
    } else if (place_counter == 6) {
      place_counter = 7;
      return true;
    } else if (place_counter == 7) {
      pn_extract(0, 1, 0, 0);
      place_counter = 8;
      return true;
    }


    else if (place_counter == 8) {
      place_counter = 9;
      return true;
    } else if (place_counter == 9) {
      pn_extract(0, 1, 0, 0), place_counter = 10;
      // return true;
    } else if (place_counter == 10) {
      place_counter = 11;
      return true;
    } else if (place_counter == 11) {
      pn_extract(1, 0, 0, 0);
      place_counter = 12;
      // return true;

      delay(1400);
      pn_retract(1, 1, 1, 1);
      pn_up(1, 1);
    } else if (place_counter == 12) place_counter = 0;
    delay(100);
    pn_up(1, 0);
  }
}

//   if (step_pneumatics == false) {
//     pn_down(1, 0);
//     delay(100);
//     /////place 13 and 24
//     if (place_counter == 2) pn_extract(1, 0, 0, 0), place_counter = 3;
//     else if (place_counter == 3) {
//       pn_extract(0, 1, 0, 0), place_counter = 4;
//       return true;
//     } else if (place_counter == 4) pn_extract(0, 1, 0, 0), place_counter = 5;
//     else if (place_counter == 5) {
//       pn_extract(1, 0, 0, 0);
//       place_counter = 6;
//       delay(1000);
//       pn_retract(1, 1, 1, 1);
//       pn_up(1, 1);
//     } else if (place_counter == 6) place_counter = 0;
//     delay(100);
//     pn_up(1, 0);
//   }
// }


bool pfr_13() {
  if (toggle_pfr == false) {
    if (flag_L13 == true) {
      pn_extract(1, 0, 0, 0), flag_L13 = false;
    } else {
      pn_retract(1, 0, 0, 0), flag_L13 = true;
    }
  } else {
    if (flag_R13 == true) {
      pn_extract(0, 0, 1, 0), flag_R13 = false;
    } else {
      pn_retract(0, 0, 1, 0), flag_R13 = true;
    }
  }
}

bool pfr_24() {
  if (toggle_pfr == false) {
    if (flag_L24 == true) {
      pn_extract(0, 1, 0, 0), flag_L24 = false;
    } else {
      pn_retract(0, 1, 0, 0), flag_L24 = true;
    }
  } else {
    if (flag_R24 == true) {
      pn_extract(0, 0, 0, 1), flag_R24 = false;
    } else {
      pn_retract(0, 0, 0, 1), flag_R24 = true;
    }
  }
}
bool pfr_ud() {
  if (toggle_pfr == false) {
    if (flag_Lud == true) {
      pn_up(1, 0), flag_Lud = false;
    } else {
      pn_down(1, 0), flag_Lud = true;
    }
  } else {
    if (flag_Rud == true) {
      pn_up(0, 1), flag_Rud = false;
    } else {
      pn_down(0, 1), flag_Rud = true;
    }
  }
}


#endif