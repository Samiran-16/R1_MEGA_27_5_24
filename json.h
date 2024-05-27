#ifndef JSON_H
#define JSON_H
#include "Variables.h"


// #define SERIAL_COM  
// #define CMD_DEBUG
// #define SERIAL_COM_3
#define JSON_REC
void get_cmd(){

// #ifdef SERIAL_COM
//  if (Serial.available()) {
//     cmd = Serial.read();
//   } else {
//     cmd = "S";
//   }

// #endif
#ifdef SERIAL_COM_3
  if (Serial3.available()) {
    command = Serial3.readStringUntil('*');
    Serial.println(command);
  } else {
    command = "S";
  }
  cmd = command.charAt(0);

  #endif

  #ifdef CMD_DEBUG
  Serial.print(cmd);
  Serial.print("  ");
  #endif
}
#ifdef JSON_REC
void json_rec(){
  if (Serial2.available() > 0) {

    json = Serial2.readStringUntil('*');
  // }
    Jsonerror = deserializeJson(doc, json);

    if (Jsonerror) {
      // Serial.print(F("deserializeJson() failed: "));
      Serial.println(Jsonerror.f_str());
      return;
    } else {
      String esp_data = doc["COM"];
      // Serial.print(" , com: ");
      // Serial.print(esp_data);
      // Serial.print("  ");
      cmd = esp_data.charAt(0);
      // Serial.print(cmd);
      // Serial.println(step_pneumatics);
      
    }
  
  }
}
#endif

#endif