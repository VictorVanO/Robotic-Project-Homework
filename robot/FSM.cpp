#include "FSM.h"
#include "Motors.h"
#include "Ultrasonic.h"

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
            if (distance > 0 && distance < 100) {  // Si un obstacle est détecté proche
                state = ObstacleDetected;
            } else {
                state = MoveForward;
            }
            break;

        case MoveForward:
            setMotorsSpeed(150);       // Régler la vitesse des moteurs
            runMotors(FORWARD);        // Faire avancer les moteurs
            if (distance > 0 && distance < 30) {  // Obstacle très proche
                state = ObstacleDetected;
            }
            break;

        case ObstacleDetected:
            stopMotors();              // Arrêter les moteurs
            if (distance >= 100) {     // Retour à un état sûr
                state = MoveForward;
            }
            break;
    }
}