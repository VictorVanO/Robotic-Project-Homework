#include "FSM_Superstar.h"



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

            // Serial.println("Robot state: Idle");
            sendMessage("Robot state: Idle");
            // Serial.print("Waiting for timer : ");
            // Serial.println(distance);
            // If there is an obstacle in less than 10cm
            if (distance > 0 && distance < 5) {
                state = OBSTACLE_WAIT_STATE;
            } if (currentTime - startTime >= timeoutDuration) {
                state = FOLLOW_LINE_STATE;
            }else {
                state = IDLE;
            }
            break;

        case FOLLOW_LINE_STATE:
            sendMessage("Robot state: Follow Line");
            if (currentTime - startTime <= 6000) //BEGINNING : GOES IN A STRAIGHT LINE : BETTER CODE
            {
                // Serial.println("Robot following line.");
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
                state = OBSTACLE_WAIT_STATE;
            } else 
            break;

        
        case OBSTACLE_WAIT_STATE:
            
            sendMessage("Robot state: Obstacle Wait");

            stopMotors();
            Serial.println("Obstacle Detected : Robot stopping");
            if (distance > 5) {
                state = FOLLOW_LINE_STATE;
                break;
            }
            else if (distance > 0 && distance < 5) {
                state = OBSTACLE_WAIT_STATE;
            }
            
            break;
        
        case PAUSE_STATE:
            sendMessage("Robot state: Pause");

            Serial.println("Robot state: Pause.");
            stopMotors();
            if (currentTime - startTime >= timeoutParty) {
                state = PARTY_STATE;
                break;
            }else {
                state = PAUSE_STATE;
            }
            if (distance > 0 && distance < 5) {
                state = OBSTACLE_WAIT_STATE;
            }
            break;
            
        case PARTY_STATE:
            sendMessage("Robot state: Party");
            Serial.println("Party time ! ");
            stopMotors();
            // Serial.println("Robot state: PARTYYY!!!!.");
            party();

    }
}