#include "FSM_Homework.h"

FSM::FSM() : state(Idle), startTime(0) {}

void FSM::init() {
    initMotors();
    initUltrasonic();
}

void FSM::run() {
    handleState();
}

void FSM::handleState() {
    float distance = readDistance();
    int direction = 0;
    int directionCounter = 0;
    const unsigned long timeoutDuration = 30000;
    // unsigned long currentTime = millis();
    delay(200);
    
    switch (state) {
        case Idle:
            Serial.println("Robot state: Idle");
            // distance = readDistance();
            Serial.print("Distance from object: ");
            Serial.println(distance);
            // If there is an obstacle in less than 10cm
            if (distance > 0 && distance < 10) {
                state = ObstacleDetected;
            } else {
                state = Idle;
            }
            break;

        case RunForward:
            Serial.println("Robot running forward.");
            // distance = readDistance(); 
            stopMotors();
            setMotorsSpeed(150);
            runMotors(FORWARD); 
            delay(500);
            if (distance > 0 && distance < 10) {
                state = ObstacleDetected;
            } else if (startTime >= timeoutDuration) {
                state = Stop;
            }
            break;

        case RunBackward:
            Serial.println("Robot running backward.");    
            distance = readDistance();
            stopMotors();
            setMotorsSpeed(150);
            runMotors(BACKWARD); 
            delay(500); 
            if (distance > 0 && distance < 10) {
                state = ObstacleDetected;
            } else if (startTime >= timeoutDuration) {
                state = Stop;
            }
            break;
        
        case ObstacleDetected:
            // Start timer
            if (startTime == 0) startTime = millis();
            stopMotors();
            Serial.print("Obstacle Detected : Robot stopping or changing direction");    
            Serial.println(direction);
            if(directionCounter >= 5){
                state = Stop;
                // break;
            }
            switch (direction){
                case 0:
                    direction = 1; //Forward
                    state = RunForward;
                    directionCounter++;
                    Serial.print("direction counter : ");
                    Serial.println(directionCounter);
                    break;
                case 1:
                    direction = 2; //Backward
                    state = RunBackward;
                    directionCounter++;
                    Serial.print("direction counter : ");
                    Serial.println(directionCounter);
                    break;
                case 2:
                    direction = 1;
                    state = RunForward;
                    directionCounter++;
                    Serial.print("direction counter : ");
                    Serial.println(directionCounter);
                    break;
            }
            break;
        
        case Stop:
            Serial.println("Robot state: Stop");
            stopMotors();
            directionCounter = 0;
            break;
    }
}