#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Create motor objects for M1 and M2
Adafruit_DCMotor *motor1 = AFMS.getMotor(3); 
Adafruit_DCMotor *motor2 = AFMS.getMotor(4); 

void setup() {
  Serial.begin(9600);
  
  // Initialize the motor shield
  AFMS.begin();
}

void loop() {
  // Run both motors at max speed for 10 seconds
  motor1->setSpeed(255);
  motor2->setSpeed(255);
  motor1->run(FORWARD);         // Turn motor 1 forward
  motor2->run(FORWARD);         // Turn motor 2 forward
  Serial.println("Motors running with max speed: M1=255, M2=255");
  delay(10000);

  motor1->run(RELEASE);         // Stop motor 1
  motor2->run(RELEASE);         // Stop motor 2
  Serial.println("Motors stopped!");
  delay(2000);
}
