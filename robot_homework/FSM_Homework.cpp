#include "FSM_Homework.h"

// Constructeur : initialisation de l'état à Idle
FSM::FSM() : state(Idle) {}

void FSM::init() {
    initMotors();  // Initialize the motors
    initUltrasonic();  // Initialize the ultrasound sensor
    initBluetooth();  // Initialize the bluetooth communication
}

void FSM::run() {
    handleState();     // Gérer la transition et l'exécution de l'état
}
int direction = 0;//Init
int directionCounter = 0;

void FSM::handleState() {
    float distance = readDistance(); // Lire la distance depuis le capteur ultrason
    
    switch (state) {
        case Idle:
            Serial.println("idle");  
            distance = readDistance();
            Serial.println(distance);  

            if (distance > 0 && distance < 10) {  // Si un obstacle est détecté à moins de 10cm
                state = ObstacleDetected;
            } else {
                state = Idle;
            }
            break;
        
        case RunForward:
            
              stopMotors();

              setMotorsSpeed(150);
              runMotors(FORWARD); 
              Serial.println("forward"); 
              delay(1000);  
              distance = readDistance(); 
              if (distance>0 && distance <= 10) {
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
            
        
        case ObstacleDetected:
            stopMotors();
            Serial.println("obstacle : stop");    
            Serial.println(direction);
            if(directionCounter>=5){
                state = Stop;
                break;
            }

            switch (direction){
                case 0:
                    direction = 1;//Forward
                    directionCounter++;
                    Serial.println("direcction counter");
                    Serial.println(directionCounter);
                    state = RunForward;
                    sendMessage("Forward")
                    break;
                case 1:
                    direction = 2;//Backward
                    state = RunBackward;
                    sendMessage("Backward")
                    directionCounter++;
                    Serial.println("direcction counter");
                    Serial.println(directionCounter);

                    break;

                case 2:
                    direction = 1;
                    state = RunForward;
                    sendMessage("Forward")
                    directionCounter++;

                    Serial.println("direction counter");
                    Serial.println(directionCounter);
                    break;
            }
            break;
        
        
        case Stop:
            Serial.print("stop");
            stopMotors();
            directionCounter = 0;

          
          break;
    }
}