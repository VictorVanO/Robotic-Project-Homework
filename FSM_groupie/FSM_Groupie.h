#ifndef FSM_H
#define FSM_H

#include "Motors.h"
#include "Bluetooth.h"
#include "Ultrasonic.h"
#include "ServoLed.h"
#include "Infrared.h"

enum RobotState {
    IDLE,
    FOLLOW_LINE,
    OBSTACLE_WAIT,
    TURN_IN_ZONE,
    PARTY
};

class FSM {
public:
    FSM();
    void init();
    void run();
    
private:
    RobotState state;
    unsigned long startTime;
    void handleState();
};

#endif