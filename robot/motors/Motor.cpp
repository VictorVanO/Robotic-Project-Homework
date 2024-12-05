#include "Motor.h"
#include <Arduino.h>

void Motor::init() {
    pinMode(3, OUTPUT);
}

void Motor::setSpeed(int speed) {
    analogWrite(3, speed);
}
