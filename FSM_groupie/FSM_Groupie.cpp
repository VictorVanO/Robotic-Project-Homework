#include "FSM_Groupie.h"

FSM::FSM() : state(IDLE), startTime(0) {}

void FSM::init() {
    initMotors();
    initUltrasonic();
    initBluetooth();
    initInfrared();
    initServoLed();
}

void FSM::run() {
    handleState();
}

void FSM::handleState() {
    float distance = readDistance();
    const unsigned long timeoutDuration = 1000;  //!!!FINAL : 75000
    const unsigned long timeoutParty = 20000;  //!!!FINAL : 100 000
    unsigned long currentTime = millis();
    
    switch (state) {
        case IDLE:
            if (startTime == 0){
              startTime = millis();
            }
            Serial.println("Robot state: Idle");
            sendMessage("Robot state: Idle");
            // Serial.print("Waiting for timer : ");
            Serial.println(distance);
            // If there is an obstacle in less than 10cm
            if (distance > 0 && distance < 10) {
                state = OBSTACLE_WAIT;
            } else if (currentTime - startTime >= timeoutDuration) {
                state = FOLLOW_LINE;
            }else {
                state = IDLE;
            }
            break;

        case FOLLOW_LINE:
            Serial.println("Robot state: Follow Line");
            sendMessage("Robot state: Follow Line");
            if (currentTime - startTime <= 6000) //BEGINNING : GOES IN A STRAIGHT LINE : BETTER CODE
            {
              setMotorsSpeed(150);
              switch (returnDirection())
              {
              case 0:
                  goForward();
                  break;
              
              case 1:
                  turnRight();
                  break;
              case 2:

                  turnLeft();
                  break;
              case 3:
                  stopMotors();
                  break;
              default:
                  break;
              }
            }

            // Serial.println("Robot following line.");
            setMotorsSpeed(150);
            switch (returnDirection2())//AFTER 6 SECS : BETTER CODE FOR TURNING
            {
            case 0:
                goForward();
                break;
            
            case 1:
                turnRight();
                break;
            case 2:

                turnLeft();
                break;
            case 3:
                stopMotors();
                break;
            default:
                break;
            }

            
            if (distance > 0 && distance < 5) {
                state = OBSTACLE_WAIT;
            } else 
            break;

        
        case OBSTACLE_WAIT:
            
            sendMessage("Robot state: Obstacle Wait");

            stopMotors();
            Serial.println("Obstacle Detected : Robot stopping");
            if (distance > 5) {
                state = FOLLOW_LINE;
                break;
            }
            else if (distance > 0 && distance < 5) {
                state = OBSTACLE_WAIT;
            }
            break;
        
        case PAUSE:
            sendMessage("Robot state: Pause");

            Serial.println("Robot state: Pause.");
            stopMotors();
            if (currentTime - startTime >= timeoutParty) {
                state = PARTY;
                break;
            }else {
                state = PAUSE;
            }
            if (distance > 0 && distance < 5) {
                state = OBSTACLE_WAIT;
            }
            break;
            
        case PARTY:
            sendMessage("Robot state: Party");
            Serial.println("Party time ! ");
            stopMotors();
            party();
    }
}