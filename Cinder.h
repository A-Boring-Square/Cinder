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