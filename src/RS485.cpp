/*
  This file is part of the ArduinoRS485 library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

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

#ifdef __MBED__
#include "pinDefinitions.h"
RS485Class::RS485Class(HardwareSerial& hwSerial, PinName txPin, PinName dePin, PinName rePin) :
  _serial(&hwSerial),
  _txPin(PinNameToIndex(txPin)),
  _dePin(PinNameToIndex(dePin)),
  _rePin(PinNameToIndex(rePin)),
  _transmisionBegun(false)
{
}
#endif

RS485Class::RS485Class(HardwareSerial& hwSerial, int txPin, int dePin, int rePin) :
  _serial(&hwSerial),
  _txPin(txPin),
  _dePin(dePin),
  _rePin(rePin),
  _transmisionBegun(false)
{
}

void RS485Class::begin(unsigned long baudrate)
{
  begin(baudrate, SERIAL_8N1, RS485_DEFAULT_PRE_DELAY, RS485_DEFAULT_POST_DELAY);
}

void RS485Class::begin(unsigned long baudrate, int predelay, int postdelay)
{
  begin(baudrate, SERIAL_8N1, predelay, postdelay);
}

void RS485Class::begin(unsigned long baudrate, uint16_t config)
{
  begin(baudrate, config, RS485_DEFAULT_PRE_DELAY, RS485_DEFAULT_POST_DELAY);
}

void RS485Class::begin(unsigned long baudrate, uint16_t config, int predelay, int postdelay)
{
  _baudrate = baudrate;
  _config = config;

  // Set only if not already initialized with ::setDelays
  _predelay = _predelay == 0 ? predelay : _predelay;
  _postdelay = _postdelay == 0 ? postdelay : _postdelay;

  if (_dePin > -1) {
    pinMode(_dePin, OUTPUT);
    digitalWrite(_dePin, LOW);
  }

  if (_rePin > -1) {
    pinMode(_rePin, OUTPUT);
    digitalWrite(_rePin, HIGH);
  }

  _transmisionBegun = false;

#if defined(ARDUINO_OPTA)
  auto _opta_uart = static_cast<UART *>(_serial);
  _opta_uart->begin(baudrate, config, true);
#else
  _serial->begin(baudrate, config);
#endif 
}

void RS485Class::end()
{
  _serial->end();

  if (_dePin > -1) {
    digitalWrite(_dePin, LOW);
    pinMode(_dePin, INPUT);
  }
  
  if (_rePin > -1) {
    digitalWrite(_rePin, LOW);
    pinMode(_rePin, INPUT);
  }
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
    setWriteError();
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
  if (_dePin > -1) {
    digitalWrite(_dePin, HIGH);
    if (_predelay) delayMicroseconds(_predelay);
  }

  _transmisionBegun = true;
}

void RS485Class::endTransmission()
{
  _serial->flush();

  if (_dePin > -1) {
    if (_postdelay) delayMicroseconds(_postdelay);
    digitalWrite(_dePin, LOW);
  }

  _transmisionBegun = false;
}

void RS485Class::receive()
{
  if (_rePin > -1) {
    digitalWrite(_rePin, LOW);
  }
}

void RS485Class::noReceive()
{
  if (_rePin > -1) {
    digitalWrite(_rePin, HIGH);
  }
}

void RS485Class::sendBreak(unsigned int duration)
{
  _serial->flush();
  _serial->end();
  pinMode(_txPin, OUTPUT);
  digitalWrite(_txPin, LOW);
  delay(duration);
  _serial->begin(_baudrate, _config);
}

void RS485Class::sendBreakMicroseconds(unsigned int duration)
{
  _serial->flush();
  _serial->end();
  pinMode(_txPin, OUTPUT);
  digitalWrite(_txPin, LOW);
  delayMicroseconds(duration);
  _serial->begin(_baudrate, _config);
}

void RS485Class::setPins(int txPin, int dePin, int rePin)
{
  _txPin = txPin;
  _dePin = dePin;
  _rePin = rePin;
}

void RS485Class::setDelays(int predelay, int postdelay)
{
  _predelay = predelay;
  _postdelay = postdelay;
}

#ifdef RS485_SERIAL_PORT
RS485Class RS485(RS485_SERIAL_PORT, RS485_DEFAULT_TX_PIN, RS485_DEFAULT_DE_PIN, RS485_DEFAULT_RE_PIN);
#else
RS485Class RS485(SERIAL_PORT_HARDWARE, RS485_DEFAULT_TX_PIN, RS485_DEFAULT_DE_PIN, RS485_DEFAULT_RE_PIN);
#endif
