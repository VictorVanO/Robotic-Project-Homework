#include "FSM_Homework.h"  // Inclusion de la FSM

FSM fsm;          // Créer une instance de la FSM

void setup() {
    Serial.begin(9600);
    fsm.init();   // Initialiser la FSM (et ses dépendances)
}

void loop() {
    fsm.run();    // Exécuter la logique de la FSM en continu
    delay(100);
}
