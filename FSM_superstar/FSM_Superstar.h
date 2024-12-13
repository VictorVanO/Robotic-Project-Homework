#ifndef FSM_H
#define FSM_H

#include "Motors.h"
#include "Bluetooth.h"
#include "Ultrasonic.h"

enum RobotState {
    Idle,
    ObstacleDetected,
    RunForward,
    RunBackward,
    Stop
};

class FSM {
public:
    FSM();
    void init();
    void run();
    
private:
    RobotState state;
    unsigned long startTime;
    int direction;
    int directionCounter;
    void handleState();
};

#endif