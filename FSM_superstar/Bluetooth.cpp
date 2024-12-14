#include "Bluetooth.h"
#include "Arduino.h"

// Define the pins
const byte rxPin = 0;
const byte txPin = 1;

// Instantiate the SoftwareSerial object
SoftwareSerial BTSerial(rxPin, txPin); // RX TX


// Function to initialize the Bluetooth module
void initBluetooth() {
    pinMode(rxPin, INPUT);   // Set the RX pin as input
    pinMode(txPin, OUTPUT);  // Set the TX pin as output
    BTSerial.begin(9600);   // Initialize Bluetooth communication
    Serial.begin(9600);     // Initialize Serial Monitor communication
}

// Function to send a message via Bluetooth
void sendMessage(String newDirection) {
    String message = "New direction: ";
    message += newDirection;
    BTSerial.println(message);
    // Serial.println("Sending via Bluetooth: " + message);
}