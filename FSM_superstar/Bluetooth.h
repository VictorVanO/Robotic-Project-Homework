#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <SoftwareSerial.h>


// Pin configurations for Bluetooth
const byte rxPin = 8;
const byte txPin = 9;
SoftwareSerial BTSerial;

// Function declarations
void initBluetooth();
void sendMessage();

#endif // BLUETOOTH_H