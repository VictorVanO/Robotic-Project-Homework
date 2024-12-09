#include "FSM_Homework.h"

FSM::FSM() : state(Idle) {}

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
    
    switch (state) {
        case Idle:
            Serial.println("Robot state: Idle");
            // distance = readDistance();
            Serial.println("Distance from object:" + distance);  
            if (distance > 0 && distance < 10) {  // If there is an obstacle
                state = ObstacleDetected;
            } else {
                state = Idle;
            }
            break;
        
        case RunForward:
              stopMotors();
              setMotorsSpeed(150);
              runMotors(FORWARD); 
              Serial.println("forward"); 
              delay(1000);  
              distance = readDistance(); 
              if (distance>0 && distance <= 10) {
                  state = ObstacleDetected;
                  
              }
            
            
            break;

        case RunBackward:
              Serial.println("backward");    
              stopMotors();
              setMotorsSpeed(150);
              runMotors(BACKWARD); 
              delay(1000); 
              distance = readDistance();      
              if (distance>0 && distance <= 10) {
                  state = ObstacleDetected;
              }
              break;
        
        case ObstacleDetected:
            stopMotors();
            Serial.println("obstacle : stop");    
            Serial.println(direction);
            if(directionCounter>=5){
                state = Stop;
                break;
            }

            switch (direction){
                case 0:
                    direction = 1;//Forward
                    directionCounter++;
                    Serial.println("direcction counter");
                    Serial.println(directionCounter);
                    state = RunForward;
                    break;
                case 1:
                    direction = 2;//Backward
                    state = RunBackward;
                    directionCounter++;
                    Serial.println("direcction counter");
                    Serial.println(directionCounter);

                    break;

                case 2:
                    direction = 1;
                    state = RunForward;
                    directionCounter++;

                    Serial.println("direction counter");
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