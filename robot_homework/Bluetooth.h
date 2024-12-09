#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <SoftwareSerial.h>


// Pin configurations for Bluetooth
const byte rxPin = 9;
const byte txPin = 8;
SoftwareSerial BTSerial;

// Function declarations
void initBluetooth();
void handleBluetoothCommunication();
void sendMessage();

#endif // BLUETOOTH_H