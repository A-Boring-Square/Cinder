# Cinder

Cinder is a header only TUI library designed to be cross platform and portable across systems with UTF-8 support, a text buffer for input and output, and a memory allocator.

Cinder targets POSIX, Unix, Linux, macOS, BSDs, Windows, and custom freestanding targets.

Cinder is built with Clang.

Freestanding targets require only an ANSI escape code compatible terminal with 256 color or true color support and a memory allocator

Cinder only requires the standard C headers `stdlib.h`, `stdbool.h`, `stdint.h`, and `string.h`.

Cinder provides a low level terminal management system for terminal input, output, screen buffering, terminal capabilities, and related functionality. Cinder does not provide a UI framework or widget system, allowing applications to build their own higher level interfaces on top of the library.

All symbols beginning with `_Cinder` are internal implementation details and should not be used directly unless you understand the function's purpose and its implications.