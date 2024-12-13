//include tous les fichiers des périphériques

//FICHIER A SUPPRIMER PAR LA SUITE


// Définition des états
enum State {
  INITIAL_WAIT_STATE,
  FOLLOW_LINE_STATE,
  OBSTACLE_WAIT_STATE,
  PAUSE_STATE,
  PARTY_STATE
};

State currentState = INITIAL_WAIT_STATE; // État initial
unsigned long timer = 0; // Pour mesurer le temps
const int resetButtonPin = 2; // Bouton de reset
const int forwardDistancePin = A0; // Capteur de distance avant
const int downDistancePin = A1; // Capteur de distance vers le bas

void setup() {
  pinMode(resetButtonPin, INPUT_PULLUP); // Configure le bouton en entrée avec résistance interne
  Serial.begin(9600); // Initialisation pour débogage
}

void loop() {
  // Lecture des entrées
  int resetButton = digitalRead(resetButtonPin);
  int forwardDistance = analogRead(forwardDistancePin);
  int downDistance = analogRead(downDistancePin);

  switch (currentState) {
    case INITIAL_WAIT_STATE:
      Serial.println("État : INITIAL_WAIT_STATE");
      if (millis() > 85000) { // Vérifie si le timer a dépassé 85 secondes
        currentState = FOLLOW_LINE_STATE;
      }
      break;

    case FOLLOW_LINE_STATE:
      Serial.println("État : FOLLOW_LINE_STATE");
      //moteurs : avancent en suivant les lignes
      if (forwardDistance < 5) { // Distance avant trop courte
        currentState = OBSTACLE_WAIT_STATE;
      } else if (downDistance > 5) { // Distance vers le bas trop grande
        currentState = PARTY_STATE;
      }

      break;

    case OBSTACLE_WAIT_STATE:
      Serial.println("État : OBSTACLE_WAIT_STATE");
      //Moteurs à l'arrêt
      if (forwardDistance > 5) { // Obstacle dégagé
        currentState = FOLLOW_LINE_STATE;
      }
      break;

    case PARTY_STATE:
      Serial.println("État : PARTY_STATE"); 
      //Moteurs : à l'arrêt
      //Bras servo : monte et descend
      //Led : s'allume et s'éteint
      if (resetButton == LOW) { // Bouton de reset pressé
        currentState = INITIAL_WAIT_STATE;
      }
      break;

    default:
      Serial.println("État inconnu, retour à l'état initial.");
      currentState = INITIAL_WAIT_STATE;
      break;
  }

  delay(100); // Petite pause pour limiter le taux de boucle
}

