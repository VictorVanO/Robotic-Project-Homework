#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <SoftwareSerial.h>
#include <Arduino.h>


// Pin configurations for Bluetooth
extern const byte rxPin;
extern const byte txPin;

// Function declarations
void initBluetooth();
void sendMessage(String newDirection);

#endif // BLUETOOTH_H