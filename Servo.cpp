#include <Servo.h>

const int startAngle = 0;  
const int endAngle = 90;   
const int stepDelay = 15;  

void initServo() {
  myServo.attach(servoPin);  
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
