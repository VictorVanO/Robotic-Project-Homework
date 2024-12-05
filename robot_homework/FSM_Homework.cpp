#include "FSM.h"

// Constructeur : initialisation de l'état à Idle
FSM::FSM() : state(Idle) {}

void FSM::init() {
    initMotors();      // Initialiser les moteurs
    initUltrasonic();    // Initialiser le capteur ultrason
}

void FSM::run() {
    handleState();     // Gérer la transition et l'exécution de l'état
}

void FSM::handleState() {
    float distance = readDistance(); // Lire la distance depuis le capteur ultrason
    int direction = 0;//Init
    int directionCounter = 0;

    
    switch (state) {
        case Idle:
            unsigned long startTime = millis();
            if (distance > 0 && distance < 10) {  // Si un obstacle est détecté à moins de 10cm
                state = ObstacleDetected;
            } else {
                state = Idle;
            }
            break;
        
        case RunForward:
            while(millis()< startTime +30000){
                stopMotors();
                setMotorsSpeed(150);
                runMotors(FORWARD);        
                if (distance <= 10) {
                    state = ObstacleDetected;
                }
            }
            state = Stop;
            
            break;
        case RunBackward:
            while(millis()< startTime +30000){
                stopMotors();
                setMotorsSpeed(150);
                runMotors(BACKWARD);        
                if (distance <= 10) {
                    state = ObstacleDetected;
                }
            }
            state = Stop;
        
        case ObstacleDetected:
            stopMotors();
            if(directionCounter>=5){
                state = Stop;
            }

            switch (direction){
                case 0:
                    direction = 1;//Forward
                    directionCounter++;
                    state = RunForward;
                    break;
                case 1:
                    direction = 2;//Backward
                    state = RunBackward;
                    break;

                case 2:
                    direction = 1;
                    state = RunForward;
                    break;
            }
            break;
        
        
        case Stop:
            stopMotors();
            
            break;
    }
}