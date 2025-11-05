#ifndef RS485_FILE_HANDLE_H
#define RS485_FILE_HANDLE_H

#include "mbed.h"

/**
 * @file RS485FileHandle.h
 * @brief Declares an mbed FileHandle that redirects stdio to the RS485 bus.
 * This is used to capture crash logs on Mbed-based boards that support RS485 but don't have other serial output options.
 */

/**
 * @brief FileHandle implementation that forwards standard I/O to ArduinoRS485.
 * The baud rate is fixed at 115200 bps. The internal logic is tuned to ensure correct RS485 transmission behavior in
 * the context of crash log output.
 */
class RS485FileHandle : public mbed::FileHandle {
public:
    /**
     * @brief Constructs a FileHandle that targets the global RS485 interface.
     */
    RS485FileHandle();

    /**
     * @brief Writes a buffer to the RS485 bus.
     * When the first write occurs, the RS485 interface is initialised automatically.
     *
     * @param buffer Data to send.
     * @param size Number of bytes to write.
     * @return Bytes written on success, or a negative error code.
     */
    virtual ssize_t write(const void* buffer, size_t size) override;
    /**
     * @brief Reads data from the RS485 bus.
     *
     * @param buffer Destination buffer.
     * @param size Maximum number of bytes to read.
     * @return Bytes read on success, or a negative error code.
     */
    virtual ssize_t read(void* buffer, size_t size) override;
    /**
     * @brief Changes the current position within the stream.
     *
     * @param offset Byte offset relative to whence.
     * @param whence Reference position, defaults to SEEK_SET.
     * @return New position on success, or -1 on error.
     */
    virtual off_t seek(off_t offset, int whence = SEEK_SET) override;
    /**
     * @brief Closes the FileHandle and ends any active transmission.
     *
     * @return 0 on success, or a negative error code.
     */
    virtual int close() override;
    /**
     * @brief Reports readiness for the requested events.
     *
     * @param events Bitmask of poll events (POLLIN, POLLOUT, ...).
     * @return Bitmask indicating the ready events.
     */
    virtual short poll(short events) const override;
    /**
     * @brief Flushes pending data to the RS485 bus.
     *
     * @return 0 on success, or a negative error code.
     */
    virtual int sync() override;
    /**
     * @brief Indicates whether the handle represents a TTY-like device.
     *
     * @return Non-zero when treated as a TTY.
     */
    virtual int isatty() const;

private:
    bool _isInitialized = false;
    bool _inTransmission = false;
    void begin();
    void begin(int baudRate);
};

/**
 * @brief Global RS485 FileHandle instance used to redirect stdio.
 */
extern RS485FileHandle RS485Console;

#endif  // RS485_FILE_HANDLE_H