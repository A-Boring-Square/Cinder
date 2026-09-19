#ifndef CINDER_IO_DEVICE_H
#define CINDER_IO_DEVICE_H

#include <stdbool.h>
#include <stddef.h>

/*
Sets up the I/O device.
state points to the platform specific state owned by the I/O device.
*/
typedef bool (*CinderIODeviceSetupFn)(void *state);

/*
Shuts down the I/O device.
state points to the platform specific state owned by the I/O device.
*/
typedef void (*CinderIODeviceShutdownFn)(void *state);

/*
Reads input from the I/O device.
buffer receives the input data.
size specifies the maximum amount of data that may be read.
read receives the amount of input data that was read.
*/
typedef bool (*CinderIODeviceReadFn)(void *state, char *buffer, size_t size, size_t *read);

/*
Writes output to the I/O device.
buffer contains the output data to write.
size specifies the amount of data to write.
*/
typedef bool (*CinderIODeviceWriteFn)(void *state, const char *buffer, size_t size);

/*
Flushes pending output from the I/O device.
*/
typedef bool (*CinderIODeviceFlushFn)(void *state);


typedef struct CinderIODevice {
    void *state;

    CinderIODeviceSetupFn setup;
    CinderIODeviceShutdownFn shutdown;

    CinderIODeviceReadFn read;
    CinderIODeviceWriteFn write;
    CinderIODeviceFlushFn flush;
} CinderIODevice;

#endif // CINDER_IO_DEVICE_H