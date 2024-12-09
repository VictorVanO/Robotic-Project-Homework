#include "Bluetooth.h"

// Instantiate the SoftwareSerial object
SoftwareSerial BTSerial(rxPin, txPin); // RX TX


void initBluetooth() {
    // Define pin modes for TX and RX
    // Set the RX pin as input (for receiving data from Bluetooth)
    pinMode(rxPin, INPUT);
    // Set the TX pin as output (for sending data to Bluetooth)
    pinMode(txPin, OUTPUT);  

    // Initialize the Bluetooth serial communication at 9600 baud
    BTSerial.begin(9600);
    
    // Initialize the Serial communication (to communicate with your computer's Serial Monitor)
    Serial.begin(9600);



void sendMessage(str newDirection) {
    String message = "New direction: ";
    message += String(newDirection);
    // Send the message to the Bluetooth serial interface
    BTSerial.print(message);
    // Send a newline to end the message cleanly
    BTSerial.println();
}