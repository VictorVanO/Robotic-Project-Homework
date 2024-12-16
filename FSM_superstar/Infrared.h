#ifndef INFRARED_H
#define INFRARED_H

#include <SoftwareSerial.h>
#include <Arduino.h>


// Define the pins
const int LEFT_IR_SENSOR = 7;
const int RIGHT_IR_SENSOR = 8;

// Function declarations
void initInfrared();
int returnDirection();
int returnDirection2();

#endif // INFRARED