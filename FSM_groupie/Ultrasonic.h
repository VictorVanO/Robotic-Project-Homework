#ifndef ULTRASONIC_H
#define ULTRASONIC_H

const int trigPin = 10;
const int echoPin = 11;

void initUltrasonic();
float readDistance();

#endif