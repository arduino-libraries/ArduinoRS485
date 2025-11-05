/**
 * This example demonstrates how to redirect the Arduino Mbed crash log output to the RS485 bus.
 * This is useful for boards that support RS485 but lack easy access to other serial output options (like the Arduino Opta)
 * 
 * This example forces a crash in the setup() function to showcase the functionality.
 * Initial author: Sebastian Romero @sebromero
 */

#include "RS485FileHandle.h"

REDIRECT_STDOUT_TO(&RS485Console) // Redirect mbed crash log output to RS485

void setup() {
  // Force a crash to demonstrate the crash log over RS485
  volatile int* p = nullptr;
  *p = 42; // Dereference null pointer to cause a crash
}

void loop() {
  // Nothing to do here
}