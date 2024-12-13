#include "Infrared.h"
#include "Arduino.h"




// Instantiate the SoftwareSerial object
SoftwareSerial BTSerial(rxPin, txPin); // RX TX


// Function to initialize the Bluetooth module
void initBluetooth() {
        // Initialize IR sensor pins
    pinMode(LEFT_IR_SENSOR, INPUT);
    pinMode(RIGHT_IR_SENSOR, INPUT); 
}

// Function to send a message via Bluetooth
void followlines() {// Read the values from the IR sensors
  int leftIR = digitalRead(LEFT_IR_SENSOR);
  int rightIR = digitalRead(RIGHT_IR_SENSOR);

  if (leftIR == HIGH && rightIR == HIGH) {
    // Both sensors on the line, move forward
    Serial.println("FORWARD");
    return ("FORWARD")
  }
  else if (leftIR == LOW && rightIR == HIGH) {
    // Left sensor on the line, turn left
    Serial.println("LEFT");
    return("LEFT")
  }
  else if (leftIR == HIGH && rightIR == LOW) {
    // Right sensor on the line, turn right
    Serial.println("RIGHT");
    return("RIGHT")

  }
  else if (leftIR == LOW && rightIR == LOW) {
    // Both sensors off the line, stop or reverse slightly
    Serial.println("BRAKE");
    return("BRAKE")

    
  }

  delay(20); // Small delay for sensor stability
}