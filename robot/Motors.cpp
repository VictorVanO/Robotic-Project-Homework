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
  // Régler la vitesse des moteurs
  motor1->setSpeed(speed);
  motor2->setSpeed(speed);
}

void runMotors(uint8_t direction) {
  // Faire tourner les moteurs dans une direction donnée
  motor1->run(direction);
  motor2->run(direction);
}

void stopMotors() {
  // Arrêter les moteurs
  motor1->run(RELEASE);
  motor2->run(RELEASE);
}