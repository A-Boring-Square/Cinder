#ifndef CINDER_INPUT_H
#define CINDER_INPUT_H
#include "config.h"
#include "terminal.h"

/*
Returns a copy of the input currently stored in the terminal input buffer
If the input buffer is empty, input is requested from the I/O device
before the input is copied
size receives the size of the copied input, excluding the null terminator
The returned buffer is allocated using CINDER_MALLOC and must be
released using CINDER_FREE
Returns NULL on failure
*/
char *CinderGetInput(CinderTerminal *terminal, size_t *size);

/*
Zeros the input buffer
*/
bool CinderClearInputBuffer(CinderTerminal *terminal);

#if defined(CINDER_IMPL) || defined(CINDER_IMPLEMENTATION)

char *CinderGetInput(CinderTerminal *terminal, size_t *size) {
    char *input;
    size_t input_size;

    if (terminal == NULL || size == NULL) {
        return NULL;
    }

    if (
        terminal->io_device == NULL ||
        terminal->io_device->read == NULL ||
        terminal->input_buffer == NULL
    ) {
        return NULL;
    }

    if (terminal->input_buffer[0] == '\0') {
        size_t read;

        read = 0;

        if (terminal->input_buffer_length == 0) {
            return NULL;
        }

        if (
            !terminal->io_device->read(
                terminal->io_device->state,
                terminal->input_buffer,
                (terminal->input_buffer_length - 1),
                &read
            )
        ) {
            return NULL;
        }
        terminal->input_buffer[read] = '\0';
    }

    input_size = CINDER_STRLEN(terminal->input_buffer);

    input = (char*)CINDER_MALLOC(input_size + 1);

    if (input == NULL) {
        return NULL;
    }

    CINDER_MEMCPY(input, terminal->input_buffer, input_size + 1);

    *size = input_size;

    return input;
}

bool CinderClearInputBuffer(CinderTerminal *terminal) {
    if (terminal == NULL || terminal->input_buffer == NULL) {
        return false;
    }

    CINDER_MEMSET(terminal->input_buffer, 0, terminal->input_buffer_length);

    return true;
}

#endif // CINDER_IMPL || CINDER_IMPLEMENTATION

#endif // CINDER_INPUT_H