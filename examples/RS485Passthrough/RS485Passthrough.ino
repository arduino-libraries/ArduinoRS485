/*
  RS485 Passthrough

  This sketch relays data sent and received between the Serial port and the RS485 interface

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the 485 device
     - Y connected to A of the 485 device
     - Z connected to B of the 485 device
     - A connected to Y of the 485 device
     - B connected to Z of the 485 device
     - Jumper positions
       - FULL set to ON
       - Z \/\/ Y set to ON, if the 485 device doesn't provide termination
       - B \/\/ A set to ON, if the 485 device doesn't provide termination

  created 4 July 2018
  by Sandeep Mistry
*/

#include <ArduinoRS485.h>

void setup() {
  Serial.begin(9600);
  RS485.begin(9600);

  // enable transmission, can be disabled with: RS485.endTransmission();
  RS485.beginTransmission();

  // enable reception, can be disabled with: RS485.noReceive();
  RS485.receive();
}

void loop() {
  if (Serial.available()) {
    RS485.write(Serial.read());
  }

  if (RS485.available()) {
    Serial.write(RS485.read());
  }
}

