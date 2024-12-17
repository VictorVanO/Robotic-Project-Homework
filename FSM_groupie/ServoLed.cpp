#include "ServoLed.h"
#include <Servo.h>
#include "Arduino.h"

Servo myServo;

void initServoLed() {
  pinMode(ledPin, OUTPUT);
  myServo.attach(9);
  myServo.write(startAngle);
}

void angle() {
  for (int angle = startAngle; angle <= endAngle; angle++) {
    myServo.write(angle);
    delay(stepDelay);
  }
  for (int angle = endAngle; angle >= startAngle; angle--) {
    myServo.write(angle);
    delay(stepDelay);
  }
}

void party() {
  angle();
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}




