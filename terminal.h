#ifndef CINDER_TERMINAL_H
#define CINDER_TERMINAL_H

#include "io_device.h"
#include "config.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct CinderTerminal {
    CinderIODevice *io_device;
    char *text_buffer;
    size_t text_buffer_length;
    char *input_buffer;
    size_t input_buffer_length;
} CinderTerminal;

/*
Sets up a new terminal
in_buffer should be zeroed before use
in_buffer_length specifies the length of the input buffer
out_buffer should have a length equal to
CINDER_BUFFER_WIDTH * CINDER_BUFFER_HEIGHT
result receives true if the terminal was created successfully
otherwise false
Returns the created terminal or NULL on failure
*/
CinderTerminal *CinderCreateTerminal(
    char *out_buffer,
    char *in_buffer,
    size_t in_buffer_length,
    CinderIODevice *device,
    bool *result
);
/*

Destroys a terminal.
The terminal must have been created using `CinderCreateTerminal` 
The input and output buffers are not freed
and the I/O Device is not freed
*/
void CinderDestroyTerminal(CinderTerminal *terminal);

#if defined(CINDER_IMPL) || defined(CINDER_IMPLEMENTATION)

CinderTerminal *CinderCreateTerminal(
    char *out_buffer,
    char *in_buffer,
    size_t in_buffer_length,
    CinderIODevice *device,
    bool *result
) {
    if (result == NULL) {
        return NULL;
    }

    *result = false;

    if (
        out_buffer == NULL ||
        in_buffer == NULL ||
        in_buffer_length== 0 ||
        device == NULL ||
        device->setup == NULL ||
        device->shutdown == NULL ||
        device->read == NULL ||
        device->write == NULL ||
        device->flush == NULL
    ) {
        return NULL;
    }

    CinderTerminal *terminal = (CinderTerminal*)CINDER_MALLOC(sizeof(CinderTerminal));

    if (terminal == NULL) {
        return NULL;
    }

    terminal->text_buffer = out_buffer;
    terminal->input_buffer = in_buffer;
    terminal->input_buffer_length = in_buffer_length;
    terminal->io_device = device;

    if (!device->setup(device->state)) {
        CINDER_FREE(terminal);
        return NULL;
    }

    *result = true;

    return terminal;
}

void CinderDestroyTerminal(CinderTerminal *terminal) {
    if (terminal == NULL) {
        return;
    }
    terminal->io_device->shutdown(terminal->io_device->state);
    CINDER_FREE(terminal);
}

#endif // CINDER_IMPL || CINDER_IMPLEMENTATION

#endif // CINDER_TERMINAL_H