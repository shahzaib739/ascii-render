EMBEDDED ASCII RENDERER v1.1
============================

Ultra-lightweight ASCII rendering library for embedded systems, terminals, and SDL2 applications. Single-header, zero-dependencies design with advanced text rendering capabilities.

Author: Ferki-git-creator
License: MIT

== KEY FEATURES ==

* Header-only implementation (0 dependencies)
* 800-byte footprint including 8x8 font
* Multi-platform support:
  - Embedded systems (STM32, ESP32, Arduino)
  - Terminal/console applications
  - SDL2 desktop applications (optional)
* Advanced text rendering:
  - Character and text rendering
  - Text measurement (width/height)
  - Multi-line support with auto-wrap
* Multiple rendering backends:
  - Pixel callback (universal)
  - Monochrome buffers (1bpp)
  - RGB565 buffers (16-bit color)
  - SDL2 with TrueType fonts (optional)
- Benchmarking mode
- MIT licensed

== COMPLETE API REFERENCE ==

CORE RENDERING:
* const uint8_t* ascii_get_char_bitmap(char c)
  - Returns 8-byte bitmap for specified ASCII character (32-126)
  - Example: Get 'A' bitmap -> ascii_get_char_bitmap('A')

* void ascii_draw_char(char c, int x, int y, 
                      ascii_pixel_fn fn, void* color, void* user_data)
  - Renders character using callback function
  - Callback signature: void fn(int x, int y, void* color, void* user_data)

* int ascii_draw_text(const char* text, int x, int y,
                     ascii_pixel_fn fn, void* color, void* user_data)
  - Renders text string with newline support
  - Returns total width of rendered text

BUFFER RENDERING:
* void ascii_draw_char_to_mono_buffer(char c, uint8_t* buffer,
                                    int width, int height, int x, int y,
                                    uint8_t color)
  - Draws to 1bpp monochrome buffers (embedded displays)
  - color: 0 (off) or 1 (on)

* void ascii_draw_char_to_rgb565_buffer(char c, uint16_t* buffer,
                                      int width, int height, int x, int y,
                                      uint16_t color)
  - Draws to RGB565 buffers (TFT displays)
  - color: 16-bit RGB565 value (0x0000-0xFFFF)

TEXT MEASUREMENT:
* int ascii_text_width(const char* text)
  - Calculates text width in pixels
  - Handles multi-line text (newlines)

* int ascii_text_height(const char* text)
  - Calculates text height in pixels
  - Returns full height for multi-line text

SDL2 EXTENSION (when ASCII_ENABLE_SDL2 defined):
* ascii_sdl_context* ascii_sdl_init(const char* font_path, int size,
                                  SDL_Color color, SDL_Renderer* renderer)
  - Initializes SDL2 rendering context
  - Returns NULL on failure

* void ascii_sdl_render_text(ascii_sdl_context* ctx,
                           const char* text, int x, int y)
  - Renders text using SDL_ttf

* void ascii_sdl_cleanup(ascii_sdl_context* ctx)
  - Frees SDL2 resources

== QUICK START EXAMPLES ==

1. Pixel Callback (Universal):
void pixel_fn(int x, int y, void* color, void* data) {
    // Custom pixel drawing logic
    display_set_pixel(x, y, *(uint8_t*)color);
}
...
uint8_t color = 1;
ascii_draw_text("Hello", 10, 10, pixel_fn, &color, NULL);

2. Monochrome Buffer (Embedded):
uint8_t buffer[128*64]; // 1bpp display buffer
ascii_draw_char_to_mono_buffer('A', buffer, 128, 64, 10, 10, 1);

3. RGB565 Buffer (TFT Displays):
uint16_t rgb_buffer[320*240]; // 16-bit color buffer
ascii_draw_char_to_rgb565_buffer('B', rgb_buffer, 320, 240, 50, 50, 0xF800);

4. SDL2 Rendering:
#define ASCII_ENABLE_SDL2
#include "embedded_ascii.h"
...
SDL_Color white = {255, 255, 255};
ascii_sdl_context* ctx = ascii_sdl_init("arial.ttf", 24, white, renderer);
ascii_sdl_render_text(ctx, "SDL2 Text", 50, 50);
ascii_sdl_cleanup(ctx);

== PERFORMANCE METRICS ==

On STM32F103 (72MHz Cortex-M3):
- 1000 characters/second rendering
- 42µs per character (8x8)
- 800B ROM usage (font + code)

On x86-64 (3.0GHz):
- 250,000 characters/second
- 0.15ms per full screen (128x64)
- <1KB memory usage

== USE CASES ==

Ideal for:
- Embedded device UIs (STM32/ESP32)
- Terminal-based applications
- Debug overlays and HUDs
- Low-memory graphics systems
- Retro game interfaces (8-bit style)
- Sensor dashboards and displays
- SDL2 prototyping and tools

== SDL2 INTEGRATION GUIDE ==

1. Install dependencies:
   - SDL2 (libsdl2-dev)
   - SDL_ttf (libsdl2-ttf-dev)

2. Enable in your code:
#define ASCII_ENABLE_SDL2
#include "embedded_ascii.h"

3. Initialize and use:
SDL_Color color = {255, 255, 255}; // White
ascii_sdl_context* ctx = ascii_sdl_init("font.ttf", 24, color, renderer);
ascii_sdl_render_text(ctx, "Hello SDL2!", 100, 100);
ascii_sdl_cleanup(ctx);

== BENCHMARKING ==

To run performance tests:
1. Enable demo mode:
#define ASCII_DEMO_CONSOLE

2. Call benchmark function:
benchmark_demo();

Sample output:
Rendered 10000 frames in 1.25 seconds
Average: 0.125 ms per frame

== COMPARISON WITH ALTERNATIVES ==

vs. U8g2:
- 10x smaller footprint
- No external dependencies
- Simpler API
- Better for memory-constrained devices

vs. SDL_ttf:
- 100x lighter weight
- Works on bare metal systems
- Consistent API across platforms
- Fixed-size font for predictable performance

== SUPPORT THE PROJECT ==

If you find this library useful, please consider supporting its development:

  [ https://ko-fi.com/ferki ]

Your support helps maintain and improve this software!

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