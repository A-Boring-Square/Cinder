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
#ifndef CINDER_DRAW_H
#define CINDER_DRAW_H

#include "terminal.h"
#include "config.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct CinderTrueColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} CinderTrueColor;

typedef struct CinderColor256 {
    uint8_t index;
} CinderColor256;

/*
Writes text to the current command buffer.

next_x and next_y receive the cursor position immediately
after the text has been written.
*/
bool CinderDrawText(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    const char *text,
    uint16_t *next_x,
    uint16_t *next_y
);

/*
Writes text using true color.

next_x and next_y receive the cursor position immediately
after the text has been written.
*/
bool CinderDrawTextTrueColor(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    const char *text,
    CinderTrueColor color,
    uint16_t *next_x,
    uint16_t *next_y
);

/*
Writes text using the ANSI 256 color palette.

next_x and next_y receive the cursor position immediately
after the text has been written.
*/
bool CinderDrawText256(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    const char *text,
    CinderColor256 color,
    uint16_t *next_x,
    uint16_t *next_y
);

/*
Writes a character at the specified position.

next_x and next_y receive the cursor position immediately
after the character has been written.
*/
bool CinderDrawChar(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    char character,
    uint16_t *next_x,
    uint16_t *next_y
);

/*
Writes a character using true color.

next_x and next_y receive the cursor position immediately
after the character has been written.
*/
bool CinderDrawCharTrueColor(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    char character,
    CinderTrueColor color,
    uint16_t *next_x,
    uint16_t *next_y
);

/*
Writes a character using the ANSI 256 color palette.

next_x and next_y receive the cursor position immediately
after the character has been written.
*/
bool CinderDrawChar256(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    char character,
    CinderColor256 color,
    uint16_t *next_x,
    uint16_t *next_y
);

bool CinderMoveCursor(CinderTerminal *terminal, uint16_t x, uint16_t y);

size_t CinderBufferCapacity(void);

/*
Submits the current command buffer to the IO device.

After successful submission, the command buffer is zeroed
and reused.
*/
bool CinderPresent(CinderTerminal *terminal);

size_t _CinderBufferCapacity(void);

bool _CinderCanAppend(CinderTerminal *terminal, size_t size);

bool _CinderAppend(CinderTerminal *terminal, const char *data, size_t size, size_t *next);

bool _CinderAppendCharacter(CinderTerminal *terminal, char character, size_t *next);

bool _CinderAppendUnsigned(CinderTerminal *terminal, uint32_t value, size_t *next);

bool _CinderMoveCursor(CinderTerminal *terminal, uint16_t x, uint16_t y, size_t *next);

bool _CinderSetTrueColor(CinderTerminal *terminal, CinderTrueColor color, size_t *next);


bool _CinderSetColor256(CinderTerminal *terminal, CinderColor256 color, size_t *next);

bool _CinderResetColor(CinderTerminal *terminal, size_t *next);

#if defined(CINDER_IMPL) || defined(CINDER_IMPLEMENTATION)

size_t _CinderBufferCapacity(void) {
    return (size_t)CINDER_BUFFER_WIDTH * (size_t)CINDER_BUFFER_HEIGHT;
}

bool _CinderCanAppend(CinderTerminal *terminal, size_t size) {
    size_t capacity;

    if (terminal == NULL) {
        return false;
    }

    if (terminal->text_buffer == NULL) {
        return false;
    }

    capacity = _CinderBufferCapacity();

    if (terminal->text_buffer_length > capacity) {
        return false;
    }

    return size <= capacity - terminal->text_buffer_length;
}

bool _CinderAppend(CinderTerminal *terminal, const char *data, size_t size, size_t *next) {
    size_t start;

    if (terminal == NULL || data == NULL || next == NULL) {
        return false;
    }

    if (!_CinderCanAppend(terminal, size)) {
        return false;
    }

    start = terminal->text_buffer_length;

    for (size_t i = 0; i < size; i++) {
        terminal->text_buffer[start + i] = data[i];
    }

    terminal->text_buffer_length += size;

    *next = terminal->text_buffer_length;

    return true;
}

bool _CinderAppendCharacter(CinderTerminal *terminal, char character, size_t *next) {
    return _CinderAppend(terminal, &character, 1, next);
}

bool _CinderAppendUnsigned(CinderTerminal *terminal, uint32_t value, size_t *next) {
    char digits[10];
    size_t count;
    size_t current;

    if (terminal == NULL || next == NULL) {
        return false;
    }

    count = 0;

    do {
        digits[count++] = (char)('0' + (value % 10));
        value /= 10;
    } while (value != 0);

    current = terminal->text_buffer_length;

    while (count != 0) {
        count--;

        if (!_CinderAppendCharacter(terminal, digits[count], &current)) {
            return false;
        }
    }

    *next = current;

    return true;
}

bool _CinderMoveCursor(CinderTerminal *terminal, uint16_t x, uint16_t y, size_t *next) {
#if CINDER_ENABLE_ANSI
    size_t current;

    if (
        terminal == NULL ||
        next == NULL ||
        x >= CINDER_BUFFER_WIDTH ||
        y >= CINDER_BUFFER_HEIGHT
) {
        return false;
    }

    current = terminal->text_buffer_length;

    if (!_CinderAppend(terminal, "\x1B[", 2, &current)) {
        return false;
    }

    if (!_CinderAppendUnsigned(terminal, (uint32_t)y + 1, &current)) {
        return false;
    }

    if (!_CinderAppendCharacter(terminal, ';', &current)) {
        return false;
    }

    if (!_CinderAppendUnsigned(terminal, (uint32_t)x + 1, &current)) {
        return false;
    }

    if (!_CinderAppendCharacter(terminal, 'H', &current)) {
        return false;
    }

    *next = current;

    return true;
#else
    (void)terminal;
    (void)x;
    (void)y;

    if (next != NULL) {
        *next = 0;
    }

    return true;
#endif
}

bool _CinderSetTrueColor(CinderTerminal *terminal, CinderTrueColor color, size_t *next) {
#if CINDER_ENABLE_ANSI
    size_t current;

    if (terminal == NULL || next == NULL) {
        return false;
    }

    current = terminal->text_buffer_length;

    if (!_CinderAppend(terminal, "\x1B[38;2;", 7, &current)) {
        return false;
    }

    if (!_CinderAppendUnsigned(terminal, color.r, &current)) {
        return false;
    }

    if (!_CinderAppendCharacter(terminal, ';', &current)) {
        return false;
    }

    if (!_CinderAppendUnsigned(terminal, color.g, &current)) {
        return false;
    }

    if (!_CinderAppendCharacter(terminal, ';', &current)) {
        return false;
    }

    if (!_CinderAppendUnsigned(terminal, color.b, &current)) {
        return false;
    }

    if (!_CinderAppendCharacter(terminal, 'm', &current)) {
        return false;
    }

    *next = current;

    return true;
#else
    (void)terminal;
    (void)color;

    if (next != NULL) {
        *next = 0;
    }

    return true;
#endif
}

bool _CinderSetColor256(CinderTerminal *terminal, CinderColor256 color, size_t *next) {
#if CINDER_ENABLE_ANSI
    size_t current;

    if (terminal == NULL || next == NULL) {
        return false;
    }

    current = terminal->text_buffer_length;

    if (!_CinderAppend(terminal, "\x1B[38;5;", 7, &current)) {
        return false;
    }

    if (!_CinderAppendUnsigned(terminal, color.index, &current)) {
        return false;
    }

    if (!_CinderAppendCharacter(terminal, 'm', &current)) {
        return false;
    }

    *next = current;

    return true;
#else
    (void)terminal;
    (void)color;

    if (next != NULL) {
        *next = 0;
    }

    return true;
#endif
}

bool _CinderResetColor(CinderTerminal *terminal, size_t *next) {
#if CINDER_ENABLE_ANSI
    if (terminal == NULL || next == NULL) {
        return false;
    }

    return _CinderAppend(terminal, "\x1B[0m", 4, next);
#else
    (void)terminal;

    if (next != NULL) {
        *next = 0;
    }

    return true;
#endif
}

static bool _CinderDrawText(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    const char *text,
    uint16_t *next_x,
    uint16_t *next_y
) {
    uint16_t current_x;
    uint16_t current_y;
    size_t next;

    if (
        terminal == NULL ||
        text == NULL ||
        next_x == NULL ||
        next_y == NULL
    ) {
        return false;
    }

    if (x >= CINDER_BUFFER_WIDTH || y >= CINDER_BUFFER_HEIGHT) {
        return false;
    }

    current_x = x;
    current_y = y;

    while (*text != '\0') {
        char character;

        character = *text;

        if (character == '\r') {
            current_x = 0;
            text++;

            continue;
        }

        if (character == '\n') {
            current_x = 0;
            text++;

            if (current_y + 1 >= CINDER_BUFFER_HEIGHT) {
                *next_x = current_x;
                *next_y = current_y;

                return true;
            }

            current_y++;

            continue;
        }
#if CINDER_SHOULD_WORD_WRAP
        if (current_x >= CINDER_WORD_WRAP_VALUE || current_x >= CINDER_BUFFER_WIDTH) {
            current_x = 0;

            if (current_y + 1 >= CINDER_BUFFER_HEIGHT) {
                *next_x = current_x;
                *next_y = current_y;

                return true;
            }

            current_y++;
        }
#else
        if (current_x >= CINDER_BUFFER_WIDTH) {
            *next_x = current_x;
            *next_y = current_y;

            return true;
        }
#endif
        if (!_CinderMoveCursor(terminal, current_x, current_y, &next)) {
            return false;
        }

        if (!_CinderAppendCharacter(terminal, character, &next)) {
            return false;
        }

        current_x++;
        text++;
    }

    *next_x = current_x;
    *next_y = current_y;

    return true;
}

bool CinderDrawText(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    const char *text,
    uint16_t *next_x,
    uint16_t *next_y
) {
    size_t old_length;

    if (
        terminal == NULL ||
        text == NULL ||
        next_x == NULL ||
        next_y == NULL
    ) {
        return false;
    }

    old_length = terminal->text_buffer_length;

    if (!_CinderDrawText(terminal, x, y, text, next_x, next_y)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    return true;
}

bool CinderDrawTextTrueColor(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    const char *text,
    CinderTrueColor color,
    uint16_t *next_x,
    uint16_t *next_y
) {
    size_t old_length;
    size_t next;

    if (
        terminal == NULL ||
        text == NULL ||
        next_x == NULL ||
        next_y == NULL
    ) {
        return false;
    }

    old_length = terminal->text_buffer_length;

    if (!_CinderSetTrueColor(terminal, color, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderDrawText(terminal, x, y, text, next_x, next_y)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderResetColor(terminal, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    return true;
}

bool CinderDrawText256(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    const char *text,
    CinderColor256 color,
    uint16_t *next_x,
    uint16_t *next_y
) {
    size_t old_length;
    size_t next;

    if (
        terminal == NULL ||
        text == NULL ||
        next_x == NULL ||
        next_y == NULL
    ) {
        return false;
    }

    old_length = terminal->text_buffer_length;

    if (!_CinderSetColor256(terminal, color, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderDrawText(terminal, x, y, text, next_x, next_y)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderResetColor(terminal, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    return true;
}

bool CinderDrawChar(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    char character,
    uint16_t *next_x,
    uint16_t *next_y
) {
    size_t old_length;
    size_t next;

    if (
        terminal == NULL ||
        next_x == NULL ||
        next_y == NULL ||
        x >= CINDER_BUFFER_WIDTH ||
        y >= CINDER_BUFFER_HEIGHT
    ) {
        return false;
    }

    old_length = terminal->text_buffer_length;

    if (!_CinderMoveCursor(terminal, x, y, &next)
    ) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderAppendCharacter(terminal, character, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }
#if CINDER_SHOULD_WORD_WRAP
    if (x + 1 >= CINDER_WORD_WRAP_VALUE || x + 1 >= CINDER_BUFFER_WIDTH) {
        *next_x = 0;

        if (y + 1 < CINDER_BUFFER_HEIGHT) {
            *next_y = y + 1;
        } else {
            *next_y = y;
        }

        return true;
    }
#endif
    if (x + 1 >= CINDER_BUFFER_WIDTH) {
        *next_x = x;
        *next_y = y;

        return true;
    }

    *next_x = x + 1;
    *next_y = y;

    return true;
}

bool CinderDrawCharTrueColor(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    char character,
    CinderTrueColor color,
    uint16_t *next_x,
    uint16_t *next_y
) {
    size_t old_length;
    size_t next;

    if (
        terminal == NULL ||
        next_x == NULL ||
        next_y == NULL ||
        x >= CINDER_BUFFER_WIDTH ||
        y >= CINDER_BUFFER_HEIGHT
    ) {
        return false;
    }

    old_length = terminal->text_buffer_length;

    if (!_CinderSetTrueColor(terminal, color, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderMoveCursor(terminal, x, y, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderAppendCharacter(terminal, character, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderResetColor(terminal, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }
#if CINDER_SHOULD_WORD_WRAP
    if (x + 1 >= CINDER_WORD_WRAP_VALUE || x + 1 >= CINDER_BUFFER_WIDTH) {
        *next_x = 0;

        if (y + 1 < CINDER_BUFFER_HEIGHT) {
            *next_y = y + 1;
        } else {
            *next_y = y;
        }

        return true;
    }
#endif
    if (x + 1 >= CINDER_BUFFER_WIDTH) {
        *next_x = x;
        *next_y = y;

        return true;
    }

    *next_x = x + 1;
    *next_y = y;

    return true;
}

bool CinderDrawChar256(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y,
    char character,
    CinderColor256 color,
    uint16_t *next_x,
    uint16_t *next_y
) {
    size_t old_length;
    size_t next;

    if (
        terminal == NULL ||
        next_x == NULL ||
        next_y == NULL ||
        x >= CINDER_BUFFER_WIDTH ||
        y >= CINDER_BUFFER_HEIGHT
    ) {
        return false;
    }

    old_length = terminal->text_buffer_length;

    if (!_CinderSetColor256(terminal, color, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderMoveCursor(terminal, x, y, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderAppendCharacter(terminal, character, &next)) {
        terminal->text_buffer_length = old_length;

        return false;
    }

    if (!_CinderResetColor(terminal, &next)
    ) {
        terminal->text_buffer_length = old_length;

        return false;
    }
#if CINDER_SHOULD_WORD_WRAP
    if (x + 1 >= CINDER_WORD_WRAP_VALUE || x + 1 >= CINDER_BUFFER_WIDTH) {
        *next_x = 0;

        if (y + 1 < CINDER_BUFFER_HEIGHT) {
            *next_y = y + 1;
        } else {
            *next_y = y;
        }

        return true;
    }
#endif
    if (x + 1 >= CINDER_BUFFER_WIDTH) {
        *next_x = x;
        *next_y = y;

        return true;
    }

    *next_x = x + 1;
    *next_y = y;

    return true;
}

bool CinderMoveCursor(
    CinderTerminal *terminal,
    uint16_t x,
    uint16_t y
) {
    size_t next;

    if (
        terminal == NULL ||
        x >= CINDER_BUFFER_WIDTH ||
        y >= CINDER_BUFFER_HEIGHT
    ) {
        return false;
    }

    return _CinderMoveCursor(
        terminal,
        x,
        y,
        &next
    );
}

size_t CinderBufferCapacity(void) {
    return _CinderBufferCapacity();
}

bool CinderPresent(CinderTerminal *terminal) {
    size_t capacity;

    if (
        terminal == NULL ||
        terminal->io_device == NULL ||
        terminal->text_buffer == NULL ||
        terminal->io_device->write == NULL
    ) {
        return false;
    }

    capacity = _CinderBufferCapacity();

    if (terminal->text_buffer_length != 0) {
        if (
            !terminal->io_device->write(
                terminal->io_device->state,
                terminal->text_buffer,
                terminal->text_buffer_length
            )
        ) {
            return false;
        }

        if (
            terminal->io_device->flush != NULL &&
            !terminal->io_device->flush(
                terminal->io_device->state
            )
        ) {
            return false;
        }
    }

    CINDER_MEMSET(terminal->text_buffer, 0, capacity);

    terminal->text_buffer_length = 0;

    return true;
}

#endif // CINDER_IMPL || CINDER_IMPLEMENTATION

#endif // CINDER_DRAW_H