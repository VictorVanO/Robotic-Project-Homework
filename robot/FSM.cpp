#include "FSM_Homework.h"

// Constructeur : initialisation des variables
FSM::FSM() : state(Idle), direction(0), directionCounter(0) {}

void FSM::init() {
    initMotors();        // Initialiser les moteurs
    initUltrasonic();    // Initialiser le capteur ultrason
}

void FSM::run() {
    handleState();       // Gérer la transition et l'exécution de l'état
}

void FSM::handleState() {
    float distance = readDistance();
    
    switch (state) {
        case Idle:
            Serial.println("Idle");
            distance = readDistance();
            Serial.println(distance);
            if (distance > 0 && distance < 10) {
                state = ObstacleDetected;
            }
            break;

        case ObstacleDetected:
            stopMotors();
            Serial.println("Obstacle Detected");
            
            if (directionCounter >= 5) {
                state = Stop;
                break;
            }

            // Logique de changement de direction
            if (direction == 0) {
                direction = 1; // Forward
                state = RunForward;
            } else if (direction == 1) {
                direction = 2; // Backward
                state = RunBackward;
            } else if (direction == 2) {
                direction = 1;
                sate = RunForward;
            }

            directionCounter++; //on incrémente directioncounter 
            break;

        case RunForward:
            stopMotors();
            setMotorsSpeed(150);
            runMotors(FORWARD);
            Serial.println("forward");
            delay(1000);  
            distance = readDistance(); 
            if (distance > 0 && distance <= 10) {
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

        case Stop:
            Serial.println("Stop");
            stopMotors();
            directionCounter = 0; 
            direction = 0;        
            break;
    }
}