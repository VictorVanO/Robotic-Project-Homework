#include "ServoLed.h"
#include <Arduino.h>
#include <Servo.h>

Servo myServo;


void initServoLed() {
    pinMode(ledPin, OUTPUT);
    pinMode(resetButtonPin, INPUT_PULLUP); // Configure le bouton en entrée avec résistance interne
    myServo.attach(10);
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
    int resetButton = digitalRead(resetButtonPin);
    // Serial.println("TIME TO PARTYYY");
    while (resetButton != LOW)
    {
        angle();
        digitalWrite(ledPin, HIGH);
        delay(1000);
        digitalWrite(ledPin, LOW);
        delay(1000);
        

    }
    Serial.println("END OF THE PARTY");

}




