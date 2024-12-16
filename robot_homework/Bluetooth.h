#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <SoftwareSerial.h>

const int rxPin = 7;
const int txPin = 8;
SoftwareSerial BTSerial;

void initBluetooth();
void sendMessage(str);

#endif // BLUETOOTH_H