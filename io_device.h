/*
MIT License

Copyright (c) 2026 A-Boring-Square

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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