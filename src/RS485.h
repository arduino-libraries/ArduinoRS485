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

#ifndef _RS485_H_INCLUDED
#define _RS485_H_INCLUDED

#include <Arduino.h>
#include "RS485_defs.h"


class RS485Class : public Stream {
  public:
    RS485Class(HardwareSerial& hwSerial, int txPin, int dePin, int rePin);

    virtual void begin(unsigned long baudrate);
    virtual void begin(unsigned long baudrate, RS485_SER_CONF_TYPE config);
    virtual void begin(unsigned long baudrate, int predelay, int postdelay);
    virtual void begin(unsigned long baudrate, RS485_SER_CONF_TYPE config, int predelay, int postdelay);
    virtual void end();
    virtual int available();
    virtual int peek();
    virtual int read(void);
    virtual void flush();
    virtual size_t write(uint8_t b);
    using Print::write; // pull in write(str) and write(buf, size) from Print
    virtual operator bool();

    void beginTransmission();
    void endTransmission();
    void receive();
    void noReceive();

    void sendBreak(unsigned int duration);
    void sendBreakMicroseconds(unsigned int duration);

    void setPins(int txPin, int dePin, int rePin);

    void setDelays(int predelay, int postdelay);

  private:
    HardwareSerial* _serial;
    int _txPin;
    int _dePin;
    int _rePin;
    int _predelay = 0;
    int _postdelay = 0;

    bool _transmisionBegun;
    unsigned long _baudrate;
    RS485_SER_CONF_TYPE _config;
};

extern RS485Class RS485;

#endif
