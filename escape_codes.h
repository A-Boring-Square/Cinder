#ifndef CINDER_ESCAPE_CODES_H
#define CINDER_ESCAPE_CODES_H

/*
Cinder ANSI/VT escape codes.
This header is exposed as part of Cinder, but is primarily used internally
by the terminal and rendering APIs.
*/

// Escape characters
#define ESC "\x1B"
#define BEL "\x07"
#define BS "\x08"

// Escape sequence introducers
#define CSI ESC "["
#define OSC ESC "]"
#define ST ESC "\\"

// CSI commands
#define CUU "A"
#define CUD "B"
#define CUF "C"
#define CUB "D"
#define CNL "E"
#define CPL "F"
#define CHA "G"
#define CUP "H"
#define ED  "J"
#define EL  "K"
#define SU  "S"
#define SD  "T"
#define HVP "f"
#define SGR "m"

// SGR parameters
#define SGR_RESET "0"
#define SGR_BOLD "1"
#define SGR_FAINT "2"
#define SGR_ITALIC "3"
#define SGR_UNDERLINE "4"
#define SGR_BLINK "5"
#define SGR_INVERT "7"
#define SGR_HIDE "8"
#define SGR_STRIKE "9"

// Foreground colors
#define SGR_FG_BLACK "30"
#define SGR_FG_RED "31"
#define SGR_FG_GREEN "32"
#define SGR_FG_YELLOW "33"
#define SGR_FG_BLUE "34"
#define SGR_FG_MAGENTA "35"
#define SGR_FG_CYAN "36"
#define SGR_FG_WHITE "37"
#define SGR_FG_DEFAULT "39"

// Background colors
#define SGR_BG_BLACK "40"
#define SGR_BG_RED "41"
#define SGR_BG_GREEN "42"
#define SGR_BG_YELLOW "43"
#define SGR_BG_BLUE "44"
#define SGR_BG_MAGENTA "45"
#define SGR_BG_CYAN "46"
#define SGR_BG_WHITE "47"
#define SGR_BG_DEFAULT "49"

// Extended colors
#define SGR_FG_256 "38;5"
#define SGR_BG_256 "48;5"
#define SGR_FG_RGB "38;2"
#define SGR_BG_RGB "48;2"

// DEC private modes
#define DECAWM_ON  "?7h"
#define DECAWM_OFF "?7l"
#define CURSOR_SHOW "?25h"
#define CURSOR_HIDE "?25l"

// OSC commands
#define OSC_WINDOW_TITLE "2"
#define OSC_HYPERLINK "8"

#ifdef CINDER_ESCAPE_CODES_USE_DESCRIPTIVE_NAMES

#define ESCAPE ESC
#define BELL BEL
#define BACKSPACE BS

#define CONTROL_SEQUENCE_INTRODUCER CSI
#define OPERATING_SYSTEM_COMMAND OSC
#define STRING_TERMINATOR ST

#define CURSOR_UP CUU
#define CURSOR_DOWN CUD
#define CURSOR_FORWARD CUF
#define CURSOR_BACK CUB
#define CURSOR_NEXT_LINE CNL
#define CURSOR_PREVIOUS_LINE CPL
#define CURSOR_HORIZONTAL_ABSOLUTE CHA
#define CURSOR_POSITION CUP

#define ERASE_DISPLAY ED
#define ERASE_LINE EL

#define SCROLL_UP SU
#define SCROLL_DOWN SD

#define HORIZONTAL_VERTICAL_POSITION HVP
#define SELECT_GRAPHIC_RENDITION SGR

#define RESET SGR_RESET
#define BOLD SGR_BOLD
#define FAINT SGR_FAINT
#define ITALIC SGR_ITALIC
#define UNDERLINE SGR_UNDERLINE
#define BLINK SGR_BLINK
#define INVERT SGR_INVERT
#define HIDE SGR_HIDE
#define STRIKE SGR_STRIKE

#define FOREGROUND_BLACK SGR_FG_BLACK
#define FOREGROUND_RED SGR_FG_RED
#define FOREGROUND_GREEN SGR_FG_GREEN
#define FOREGROUND_YELLOW SGR_FG_YELLOW
#define FOREGROUND_BLUE SGR_FG_BLUE
#define FOREGROUND_MAGENTA SGR_FG_MAGENTA
#define FOREGROUND_CYAN SGR_FG_CYAN
#define FOREGROUND_WHITE SGR_FG_WHITE
#define FOREGROUND_DEFAULT SGR_FG_DEFAULT

#define BACKGROUND_BLACK SGR_BG_BLACK
#define BACKGROUND_RED SGR_BG_RED
#define BACKGROUND_GREEN SGR_BG_GREEN
#define BACKGROUND_YELLOW SGR_BG_YELLOW
#define BACKGROUND_BLUE SGR_BG_BLUE
#define BACKGROUND_MAGENTA SGR_BG_MAGENTA
#define BACKGROUND_CYAN SGR_BG_CYAN
#define BACKGROUND_WHITE SGR_BG_WHITE
#define BACKGROUND_DEFAULT SGR_BG_DEFAULT

#define FOREGROUND_256 SGR_FG_256
#define BACKGROUND_256 SGR_BG_256

#define FOREGROUND_RGB SGR_FG_RGB
#define BACKGROUND_RGB SGR_BG_RGB

#define AUTO_WRAP_ENABLE DECAWM_ON
#define AUTO_WRAP_DISABLE DECAWM_OFF

#define WINDOW_TITLE OSC_WINDOW_TITLE
#define HYPERLINK OSC_HYPERLINK

#endif // CINDER_ESCAPE_CODES_USE_DESCRIPTIVE_NAMES

#endif // CINDER_ESCAPE_CODES_H