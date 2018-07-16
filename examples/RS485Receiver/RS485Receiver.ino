/*
  RS485 Receiver

  This sketch receives data over RS485 interface and outputs the data to the Serial interface

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the 485 device
     - A connected to A/Y of the 485 device
     - B connected to B/Z of the 485 device
     - Jumper positions
       - FULL set to ON
       - A \/\/ B set to OFF

  created 4 July 2018
  by Sandeep Mistry
*/

#include <ArduinoRS485.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  RS485.begin(9600);

  // enable reception, can be disabled with: RS485.noReceive();
  RS485.receive();
}

void loop() {
  if (RS485.available()) {
    Serial.write(RS485.read());
  }
}

