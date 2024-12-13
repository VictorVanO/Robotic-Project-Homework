#include <Servo.h>

Servo myServo;  
const int servoPin = 6;

const int startAngle = 0;  
const int endAngle = 90;   
const int stepDelay = 15;  

void setup() {
  myServo.attach(servoPin);  
  myServo.write(startAngle); 
}

void loop() {
  for (int angle = startAngle; angle <= endAngle; angle++) {
    myServo.write(angle);  
    delay(stepDelay);      
  }

  for (int angle = endAngle; angle >= startAngle; angle--) {
    myServo.write(angle);  
    delay(stepDelay);      
  }
}
