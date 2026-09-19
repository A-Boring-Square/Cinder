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
#ifndef CINDER_CONFIG_H
#define CINDER_CONFIG_H

#include <stdbool.h>

/*
Cinder global configuration.
Every setting can be overridden by defining the corresponding macro
before including Cinder.
*/

/*
Freestanding mode
default is false
*/
#ifndef CINDER_IS_FREESTANDING
#define CINDER_IS_FREESTANDING false
#endif

/*
Memory Allocator and utilities setup
Hosted builds use the standard libc allocator and utilities by default.
Freestanding builds must provide all allocator and utility functions.
*/
#if CINDER_IS_FREESTANDING
#if !defined(CINDER_MALLOC) || \
!defined(CINDER_FREE) || \
!defined(CINDER_REALLOC) || \
!defined(CINDER_CALLOC) || \
!defined(CINDER_MEMSET) || \
!defined(CINDER_MEMCPY) || \
!defined(CINDER_STRLEN)
#error Freestanding Cinder builds require CINDER_MALLOC, CINDER_FREE, CINDER_REALLOC, CINDER_CALLOC, CINDER_MEMSET, CINDER_MEMCPY and CINDER_STRLEN
#endif
#else
#include <stdlib.h>
#include <string.h>
#ifndef CINDER_MALLOC
#define CINDER_MALLOC malloc
#endif
#ifndef CINDER_FREE
#define CINDER_FREE free
#endif
#ifndef CINDER_REALLOC
#define CINDER_REALLOC realloc
#endif
#ifndef CINDER_CALLOC
#define CINDER_CALLOC calloc
#endif
#ifndef CINDER_MEMSET
#define CINDER_MEMSET memset
#endif
#ifndef CINDER_MEMCPY
#define CINDER_MEMCPY memcpy
#endif
#ifndef CINDER_STRLEN
#define CINDER_STRLEN strlen
#endif
#endif

/*
Width of the Cinder buffers in characters.
Stored as a uint16_t.
Valid range: 1 - 65535.
Default: 255
*/
#ifndef CINDER_BUFFER_WIDTH
#define CINDER_BUFFER_WIDTH 255
#endif

/*
Height of the Cinder buffers in characters.
Stored as a uint16_t.
Valid range: 1 - 65535.
Default: 255
*/
#ifndef CINDER_BUFFER_HEIGHT
#define CINDER_BUFFER_HEIGHT 255
#endif

/*
Compile time validation for the buffers dimensions.
The dimensions must fit within a uint16_t.
*/
#if CINDER_BUFFER_WIDTH < 1 || CINDER_BUFFER_WIDTH > 65535
#error CINDER_BUFFER_WIDTH must be between 1 and 65535
#endif

#if CINDER_BUFFER_HEIGHT < 1 || CINDER_BUFFER_HEIGHT > 65535
#error CINDER_BUFFER_HEIGHT must be between 1 and 65535
#endif

/*
Enables or disables automatic word wrapping.
When enabled, text exceeding CINDER_WORD_WRAP_VALUE is wrapped
onto the following line.
Default: true
*/
#ifndef CINDER_SHOULD_WORD_WRAP
#define CINDER_SHOULD_WORD_WRAP true
#endif

/*
Maximum line width used when word wrapping is enabled.
By default this matches the buffers width. It can be overridden
independently to wrap text before reaching the edge of the buffer.
Default: CINDER_BUFFER_WIDTH
*/
#ifndef CINDER_WORD_WRAP_VALUE
#define CINDER_WORD_WRAP_VALUE CINDER_BUFFER_WIDTH
#endif

/*
Compile time validation for the word wrap value.
The dimensions must fit within a uint16_t.
*/
#if CINDER_WORD_WRAP_VALUE < 1 || CINDER_WORD_WRAP_VALUE > 65535
#error CINDER_WORD_WRAP_VALUE must be between 1 and 65535
#endif

/*
Enables ANSI/VT escape sequence output.
Default: true
*/
#ifndef CINDER_ENABLE_ANSI
#define CINDER_ENABLE_ANSI true
#endif

// PLATFORM DETECTION

/*
Windows
*/
#if defined(_WIN32) || defined(_WIN64)
#define CINDER_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#endif

/*
Linux
*/
#if defined(__linux__) && !defined(__ANDROID__)
#define CINDER_PLATFORM_LINUX
#endif

/*
macOS
*/
#if defined(__APPLE__) && defined(__MACH__)
#define CINDER_PLATFORM_MACOS
#endif

/*
Unix/POSIX like
*/
#if defined(_POSIX_VERSION) || \
defined(__unix__) || \
defined(__unix) || \
defined(CINDER_PLATFORM_MACOS) || \
defined(CINDER_PLATFORM_LINUX) || \
defined(__FreeBSD__) || \
defined(__NetBSD__) || \
defined(__OpenBSD__) || \
defined(__DragonFly__)
#define CINDER_PLATFORM_UNIX_POSIX_LIKE
#endif

/*
Freestanding
*/
#if CINDER_IS_FREESTANDING == true
#define CINDER_PLATFORM_FREESTANDING
#endif



#endif // CINDER_CONFIG_H