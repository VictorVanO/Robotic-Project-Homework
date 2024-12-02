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

    switch (state) {
        case Idle:
            if (distance > 0 && distance < 10) {  // Si un obstacle est détecté à moins de 10cm
                state = ObstacleDetected;
            } else {
                state = ObstacleNotDetected;
            }
            break;
        
        case ObstacleDetected:
            setMotorsSpeed(150);
            runMotors(FORWARD);        
            if (distance >= 10) {
                state = ObstacleNotDetected;
            }
            break;

        case ObstacleNotDetected:
            stopMotors();
            if (distance > 0 && distance < 10) {
                state = ObstacleDetected;
            }
            break;

    }
}