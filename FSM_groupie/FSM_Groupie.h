#ifndef FSM_H
#define FSM_H

#include "Motors.h"
#include "Bluetooth.h"
#include "Ultrasonic.h"
#include "ServoLed.h"
#include "Infrared.h"

enum RobotState {
    IDLE,
    FOLLOW_LINE_STATE,
    OBSTACLE_WAIT_STATE,
    PAUSE_STATE,
    PARTY_STATE
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