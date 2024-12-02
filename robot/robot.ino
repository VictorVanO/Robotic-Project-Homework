#include <Wire.h>
#include "motors/Motor.h"

void setup() {
  Serial.begin(9600);

  initMotors();
}

void loop() {
  setMotorsSpeed(255);
  runMotors(FORWARD);
  Serial.println("Motors running with max speed: M1=255, M2=255");
  delay(10000);

  stopMotors();
  Serial.println("Motors stopped!");
  delay(2000);
}