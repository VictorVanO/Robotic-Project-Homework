#include "Motors.h"

// Création de l'objet pour le shield moteur
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Création des objets pour les moteurs
Adafruit_DCMotor *motor1 = AFMS.getMotor(3);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);

void initMotors() {
  // Initialiser le shield et les moteurs
  AFMS.begin();
}

void setMotorsSpeed(uint8_t speed) {
  motor1->setSpeed(speed);
  motor2->setSpeed(speed);
}

void runMotors(uint8_t direction) {
  motor1->run(direction);
  motor2->run(direction);
}

void turnLeft() {
    motor1->run(RELEASE);  // Arrêter le moteur gauche
    motor2->run(FORWARD);  // Faire tourner le moteur droit
}

void turnRight() {
    motor1->run(FORWARD);  // Faire tourner le moteur gauche
    motor2->run(RELEASE);  // Arrêter le moteur droit
}

void stopMotors() {
  motor1->run(RELEASE);
  motor2->run(RELEASE);
}

