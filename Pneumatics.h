#ifndef PNEUMATICS_H
#define PNEUMATICS_H


bool pn_retract(bool r13_L, bool r24_L, bool r13_R, bool r24_R) {
  if (r13_L) digitalWrite(R13_L, HIGH);
  if (r24_L) digitalWrite(R24_L, HIGH);
  if (r13_R) digitalWrite(R13_R, HIGH);
  if (r24_R) digitalWrite(R24_R, HIGH);
  delay(500);
  digitalWrite(R13_L, LOW);
  digitalWrite(R24_L, LOW);
  digitalWrite(R13_R, LOW);
  digitalWrite(R24_R, LOW);
}

bool pn_extract(bool e13_L, bool e24_L, bool e13_R, bool e24_R) {
  if (e13_L) digitalWrite(E13_L, HIGH);
  if (e24_L) digitalWrite(E24_L, HIGH);
  if (e13_R) digitalWrite(E13_R, HIGH);
  if (e24_R) digitalWrite(E24_R, HIGH);
  delay(500);
  digitalWrite(E13_L, LOW);
  digitalWrite(E24_L, LOW);
  digitalWrite(E13_R, LOW);
  digitalWrite(E24_R, LOW);
}

bool pn_down(bool down_L, bool down_R) {
  if (down_L) digitalWrite(DOWN_L, HIGH);
  if (down_R) digitalWrite(DOWN_R, HIGH);
  delay(delay_pn);
  digitalWrite(DOWN_L, LOW);
  digitalWrite(DOWN_R, LOW);
}

bool pn_up(bool up_L, bool up_R) {
  if (up_L) digitalWrite(UP_L, HIGH);
  if (up_R) digitalWrite(UP_R, HIGH);
  delay(delay_pn);
  digitalWrite(UP_L, LOW);
  digitalWrite(UP_R, LOW);
}


#endif