#ifndef SERVOLED_H
#define SERVOLED_H

const int ledPin = 6;
const int startAngle = 90;
const int endAngle = 180;
const int stepDelay = 15;

void initServoLed();
void party();
void angle();


#endif