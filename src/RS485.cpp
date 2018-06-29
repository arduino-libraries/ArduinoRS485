/*
  This file is part of the RS485 library.
  Copyright (C) 2018  Arduino AG (http://www.arduino.cc/)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "RS485.h"

RS485Class::RS485Class(HardwareSerial& hwSerial, int rePin, int dePin) :
  _serial(&hwSerial),
  _rePin(rePin),
  _dePin(dePin),
  _transmisionBegun(false)
{
}

void RS485Class::begin(unsigned long baudrate)
{
  begin(baudrate, SERIAL_8N1);
}

void RS485Class::begin(unsigned long baudrate, uint16_t config)
{
  _baudrate = baudrate;
  _config = config;

  pinMode(_rePin, OUTPUT);
  pinMode(_dePin, OUTPUT);

  digitalWrite(_rePin, HIGH);
  digitalWrite(_dePin, LOW);

  _transmisionBegun = false;

  _serial->begin(baudrate, config);
}

void RS485Class::end()
{
  _serial->end();

  digitalWrite(_rePin, LOW);
  digitalWrite(_dePin, LOW);

  pinMode(_rePin, INPUT);
  pinMode(_dePin, INPUT);
}

int RS485Class::available()
{
  return _serial->available();
}

int RS485Class::peek()
{
  return _serial->peek();
}

int RS485Class::read(void)
{
  return _serial->read();
}

void RS485Class::flush()
{
  return _serial->flush();
}

size_t RS485Class::write(uint8_t b)
{
  if (!_transmisionBegun) {
    return 0;
  }

  return _serial->write(b);
}

RS485Class::operator bool()
{
  return true;
}

void RS485Class::beginTransmission()
{
  digitalWrite(_dePin, HIGH);
  delay(1);

  _transmisionBegun = true;
}

void RS485Class::endTransmission()
{
  _serial->flush();
  delay(1);
  digitalWrite(_dePin, LOW);
  

  _transmisionBegun = false;
}

void RS485Class::receive()
{
  digitalWrite(_rePin, LOW);
  delay(1);
}

void RS485Class::noReceive()
{
  delay(1);
  digitalWrite(_rePin, HIGH);
}

void RS485Class::sendBreak(unsigned int duration)
{
  _serial->end();
  delay(duration);
  _serial->begin(_baudrate, _config);
}

void RS485Class::setPins(int rePin, int dePin)
{
  _rePin = rePin;
  _dePin = dePin;
}

RS485Class RS485(SERIAL_PORT_HARDWARE, RS845_DEFAULT_RE_PIN, RS845_DEFAULT_DE_PIN);
