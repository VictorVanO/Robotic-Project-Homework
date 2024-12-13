#include "FSM_Superstar.h"



FSM::FSM() : state(IDLE), startTime(0) {}


void FSM::init() {
    initMotors();
    initUltrasonic();
    initBluetooth();
    initInfrared();

}

void FSM::run() {
    handleState();
}

void FSM::handleState() {
    float distance = readDistance();
    const unsigned long timeoutDuration = 5000;  //!!!FINAL : 75000
    const unsigned long timeoutParty = 20000;  //!!!FINAL : 100 000
    unsigned long currentTime = millis();
    
    switch (state) {
        case IDLE:
            if (startTime == 0):
                startTime = millis();
            Serial.println("Robot state: Idle");
            Serial.print("Waiting for timer : ");
            Serial.println(distance);
            // If there is an obstacle in less than 10cm
            if (distance > 0 && distance < 10) {
                state = OBSTACLE_WAIT_STATE;
            } if (currentTime - startTime >= timeoutDuration) {
                state = FOLLOW_LINE_STATE;
            }else {
                state = IDLE;
            }
            break;

        case FOLLOW_LINE_STATE:
            Serial.println("Robot following line.");
            setMotorsSpeed(100);
            switch (returnDirection())
            {
            case "FORWARD":
                goForward();
                break;
            
            case "LEFT":
µ                turnLeft();
                break;
            case "RIGHT":
                turnRight();
                break;
            case "BRAKE":
                stopMotors();
                break;
            default:
                break;
            }

            
            if (distance > 0 && distance < 10) {
                state = ObstacleDetected;
            } else 
            break;

        
        case OBSTACLE_WAIT_STATE:
            // Start timer
            
            
            stopMotors();
            Serial.print("Obstacle Detected : Robot stopping");
            if (distance > 10) {
                state = FOLLOW_LINE_STATE;
                break;
            }
            else if (distance > 0 && distance < 10) {
                state = OBSTACLE_WAIT_STATE;
            }
            
            break;
        
        case PAUSE_STATE:
            Serial.println("Robot state: Pause.");
            stopMotors();
            if (currentTime - startTime >= timeoutParty) {
                state = PARTY_STATE;
                break;
            }else {
                state = PAUSE_STATE;
            }
            if (distance > 0 && distance < 10) {
                state = OBSTACLE_WAIT_STATE;
            }
            break;
            
        case PARTY_STATE:
            stopMotors();
            Serial.println("Robot state: PARTYYY!!!!.");
            if (currentTime - startTime >= timeoutParty) {
                state = PARTY_STATE;
                break;
            }else {
                state = PAUSE_STATE;
            }
            break;

    }
}