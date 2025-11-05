#include "RS485FileHandle.h"
#include <ArduinoRS485.h>
#include <errno.h>

RS485FileHandle::RS485FileHandle() {}

void RS485FileHandle::begin() {
    RS485FileHandle::begin(115200);  // Default baud rate
}

void RS485FileHandle::begin(int baudRate) {
    // Ensure idempotent initialization
    if (!_isInitialized) {
        const auto bitduration { 1.f / baudRate };
        const auto wordlen { 9.6f }; // OR 10.0f depending on the channel configuration
        const auto preDelayBR { bitduration * wordlen * 3.5f * 1e6 };
        const auto postDelayBR { bitduration * wordlen * 3.5f * 1e6 };

        RS485.begin(baudRate);
        RS485.setDelays(preDelayBR, postDelayBR);
        RS485.noReceive();
        _isInitialized = true;
    }
}

ssize_t RS485FileHandle::write(const void* buffer, size_t size) {
    begin();  // Ensure RS485 is initialized

    // Avoid repeatedly starting transmission if already in progress
    // as mbed calls write multiple times for a single output operation.
    // This otherwise results in mangled output on RS485.
    
    if (!_inTransmission) {
        RS485.beginTransmission();
        _inTransmission = true;
    }

    size_t writtenBytes = RS485.write(static_cast<const uint8_t*>(buffer), size);    
    return writtenBytes;  // Return the number of bytes written
}

ssize_t RS485FileHandle::read(void* buffer, size_t size) {
    // Not implemented for RS485 output redirection
    return -ENOSYS;
}

off_t RS485FileHandle::seek(off_t offset, int whence) {
    return -ESPIPE;  // Not seekable
}

int RS485FileHandle::close() {
    if (_inTransmission) {
        RS485.endTransmission();
        _inTransmission = false;
    }
    RS485.end();
    _isInitialized = false;
    return 0;
}

short RS485FileHandle::poll(short events) const {
    return POLLOUT;  // Ready to write
}

int RS485FileHandle::sync() {
    if (_inTransmission) {
        RS485.endTransmission();
        _inTransmission = false;
    }
    return 0;
}

int RS485FileHandle::isatty() const {
    return true;
}

// Global instance for stdout redirection
RS485FileHandle RS485Console;