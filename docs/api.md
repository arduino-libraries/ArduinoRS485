# Arduino RS485 library

## Methods

### `begin()`

Initializes the RS485 object communication speed.

#### Syntax 

```
RS485.begin(baudrate)
```

#### Parameters

* _baudrate_: communication speed in bits per second (baud).

#### Returns

None.

#### See also

* [end()](#end)
* [available()](#available)
* [peek()](#peek)
* [read()](#read)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `end()`

Disables RS485 communication.

#### Syntax 

```
RS485.end()
```

#### Parameters

None. 

#### Returns

None.

#### See also

* [begin()](#begin)
* [available()](#available)
* [peek()](#peek)
* [read()](#read)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `available()`

Get the number of bytes (characters) available for reading from the RS485 port. This is data that already arrived and is stored in the serial receive buffer.

#### Syntax 

```
RS485.available()
```

#### Parameters

None. 

#### Returns

The number of bytes available to read.

#### See also

* [begin()](#begin)
* [end()](#end)
* [peek()](#peek)
* [read()](#read)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `peek()`

Returns the next byte (character) of the incoming serial data without removing it from the internal serial buffer. That is, successive calls to peek() will return the same character, as will the next call to read().

#### Syntax 

```
RS485.peek()
```

#### Parameters

None. 

#### Returns

The first byte of incoming serial data available or -1 if no data is available. 

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [read()](#read)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `read()`

Reads incoming serial data.

#### Syntax 

```
RS485.read()
```

#### Parameters

None. 

#### Returns

The first byte of incoming serial data available or -1 if no data is available. 

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `write()`

Writes binary data to the serial port. This data is sent as a byte or series of bytes.

#### Syntax 

```
RS485.write(uint8_t b)
```

#### Parameters

* _b_: unsigned char.

#### Returns

The number of bytes written.

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `flush()`

Waits for the transmission of outgoing serial data to complete.

#### Syntax 

```
RS485.flush()
```

#### Parameters

None.

#### Returns

None.

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [write()](#write)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `beginTransmission()`

Enables RS-485 transmission.

#### Syntax 

```
RS485.beginTransmission()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
#include <ArduinoRS485.h>

int counter = 0;

void setup() {
  RS485.begin(9600);
}

void loop() {
  RS485.beginTransmission();
  RS485.print("Counter: ");
  RS485.println(counter);
  RS485.endTransmission();

  counter++;

  delay(1000);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [write()](#write)
* [flush()](#flush)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `endTransmission()`

Disables RS-485 transmission.

#### Syntax 

```
RS485.endTransmission()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
#include <ArduinoRS485.h>

int counter = 0;

void setup() {
  RS485.begin(9600);
}

void loop() {
  RS485.beginTransmission();
  RS485.print("Counter: ");
  RS485.println(counter);
  RS485.endTransmission();

  counter++;

  delay(1000);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `receive()`

Enables reception. 

#### Syntax 

```
RS485.receive()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
#include <ArduinoRS485.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  RS485.begin(9600);

  // Enable data reception
  RS485.receive();
}

void loop() {
  if (RS485.available()) {
    Serial.write(RS485.read());
  }
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `noReceive()`

Disables reception. 

#### Syntax 

```
RS485.noReceive()
```

#### Parameters

None.

#### Returns

None.

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `sendBreak()`

Sends a serial break signal for the specified duration in milliseconds.

#### Syntax 

```
RS485.sendBreak(unsigned int duration)
```

#### Parameters

* _duration_: Duration of the break signal in milliseconds.

#### Returns

None.

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)
* [setPins()](#setpins)

### `sendBreakMicroseconds()`

Sends a serial break signal for the specified duration in microseconds.

#### Syntax 

```
RS485.sendBreak(unsigned int duration)
```

#### Parameters

* _duration_: Duration of the break signal in microseconds.

#### Returns

None.

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [setPins()](#setpins)

### `setPins()`

Modify the pins used to communicate with the MAX3157 chipset. By default the library uses pin 14 for TX, pin A6 for drive output enable, and pin A5 for receiver output enable.

#### Syntax 

```
RS485.setPins(int txPin, int dePin, int rePin)
```

#### Parameters

* _txPin_: transmission pin (used to send break signals).
* _dePin_: drive output enable pin.
* _rePin_: receiver output enable pin.

#### Returns

None.

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [peak()](#peak)
* [read()](#write)
* [write()](#write)
* [flush()](#flush)
* [beginTransmission()](#begintransmission)
* [endTransmission()](#endtransmission)
* [receive()](#receive)
* [noReceive()](#noreceive)
* [sendBreak()](#sendbreak)
* [sendBreakMicroseconds()](#sendbreakmicroseconds)