/*
  RS485 Sender

  This sketch periodically sends a string over the RS485 interface

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the 485 device
     - Y connected to A of the 485 device
     - Z connected to B of the 485 device
     - Jumper positions
       - FULL set to ON
       - Z \/\/ Y set to ON

  created 4 July 2018
  by Sandeep Mistry
*/

#include <ArduinoRS485.h>

int counter = 0;

void setup() {
  RS485.begin(9600);
}

void loop() {
  RS485.beginTransmission();
  RS485.print("hello ");
  RS485.println(counter);
  RS485.endTransmission();

  counter++;

  delay(1000);
}

