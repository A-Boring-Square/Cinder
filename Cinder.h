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
#ifndef CINDER_H
#define CINDER_H
#include "config.h"
#include "escape_codes.h"
#include "io_device.h"
#include "terminal.h"
#include "draw.h"
#include "input.h"

#ifndef CINDER_VERSION_MAJOR
#define CINDER_VERSION_MAJOR 0
#endif

#ifndef CINDER_VERSION_MINOR
#define CINDER_VERSION_MINOR 1
#endif

#ifndef CINDER_VERSION_PATCH
#define CINDER_VERSION_PATCH 0
#endif

#ifndef CINDER_VERSION
#define CINDER_VERSION CINDER_VERSION_MAJOR # CINDER_VERSION_MINOR # CINDER_VERSION_PATCH)
#endif

#endif // CINDER_H