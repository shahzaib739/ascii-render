EMBEDDED ASCII FONT LIBRARY
===========================

Header-only ASCII font rendering library for embedded systems and resource-constrained environments. Provides simple, efficient text rendering capabilities with zero dependencies.

Version: 1.0
Author: Ferki-git-creator
License: MIT

== FEATURES ==

- Single header file implementation
- No external dependencies
- Support for monochrome and RGB565 displays
- 8x8 pixel ASCII font (characters 32-126)
- Callback-based rendering for maximum portability
- Buffer-based rendering for common display types
- Text measurement utilities
- Console-based demo mode
- MIT licensed

== USAGE ==

1. Copy embedded_ascii.h to your project
2. Include the header in your code:
   #include "embedded_ascii.h"

=== BASIC USAGE ===

// Draw text using pixel callback
void my_pixel_fn(int x, int y, void* color, void* user_data) {
    // Your display drawing logic here
}

ascii_draw_text("Hello World", 10, 10, my_pixel_fn, &color, NULL);

// Draw to monochrome buffer
uint8_t buffer[128*64];
ascii_draw_char_to_mono_buffer('A', buffer, 128, 64, 10, 10, 1);

// Draw to RGB565 buffer
uint16_t rgb_buffer[320*240];
ascii_draw_char_to_rgb565_buffer('B', rgb_buffer, 320, 240, 20, 20, 0xFFFF);

=== TEXT MEASUREMENT ===

int width = ascii_text_width("Hello");
int height = ascii_text_height("Multi\nline");

=== DEMO MODE ===

#define ASCII_DEMO_CONSOLE
#include "embedded_ascii.h"

int main() {
    ascii_demo_console();
    return 0;
}

== API REFERENCE ==

- const uint8_t* ascii_get_char_bitmap(char c)
- void ascii_draw_char(char c, int x, int y, ascii_pixel_fn fn, void* color, void* user_data)
- int ascii_draw_text(const char* text, int x, int y, ascii_pixel_fn fn, void* color, void* user_data)
- void ascii_draw_char_to_mono_buffer(...)
- void ascii_draw_char_to_rgb565_buffer(...)
- int ascii_text_width(const char* text)
- int ascii_text_height(const char* text)

== PERFORMANCE ==

Optimized for embedded systems:
- All functions static inline
- No heap allocations
- Minimal stack usage
- Efficient pixel rendering
- Small memory footprint (font data < 800 bytes)

== SUPPORT THE DEVELOPER ==

If you appreciate this software and use it in your projects, 
please consider supporting its development:

  [ https://ko-fi.com/ferki ]

Your donations help maintain and improve this library!

== LICENSE ==

MIT License

Copyright (c) 2023 Ferki-git-creator

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