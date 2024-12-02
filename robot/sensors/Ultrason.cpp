// Ultrason.cpp
#include "Ultrason.h"
#include <Arduino.h>

void Ultrason::init() {
    pinMode(8, OUTPUT); // Exemple : pin trigger
    pinMode(9, INPUT);  // Exemple : pin echo
}

int Ultrason::readDistance() {
    // Logique pour lire la distance
    return 0; // Valeur fictive pour l'exemple
}