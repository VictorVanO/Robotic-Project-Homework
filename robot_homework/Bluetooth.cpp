#include "Bluetooth.h"

// Define the pins


// Instantiate the SoftwareSerial object
SoftwareSerial BTSerial(rxPin, txPin); // RX TX

// Global variables
String messageBuffer = "";
String message = "";

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

// Function to handle Bluetooth communication
void handleBluetoothCommunication() {
    // Check if data is available to read from Bluetooth
    while (BTSerial.available() > 0) {
        char data = (char) BTSerial.read();  // Read one byte of data from the Bluetooth module
        messageBuffer += data;               // Add the received data to the message buffer

        // If a semicolon (;) is detected, process the message
        if (data == ';') {
            message = messageBuffer;        // Store the full message up to the semicolon
            messageBuffer = "";             // Clear the buffer for the next message

            // Print the received message to the Serial Monitor
            Serial.print(message);

            // Send a response back to the Bluetooth terminal
            message = "You sent " + message;
            BTSerial.print(message);  // Send the response via Bluetooth
        }
    }
}

void sendMessage(str newDirection) {
    String message = "New direction: ";
    message += String(newDirection);
    // Send the message to the Bluetooth serial interface
    BTSerial.print(message);
    // Send a newline to end the message cleanly
    BTSerial.println();
}