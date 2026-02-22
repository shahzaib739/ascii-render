# ascii-render: Header-only ASCII Font Renderer for Embedded Systems

Releases and assets: https://github.com/shahzaib739/ascii-render/releases

[![Releases](https://img.shields.io/badge/releases-download-blue?logo=github&logoColor=white)](https://github.com/shahzaib739/ascii-render/releases)

ascii-render is a header-only C library that renders ASCII fonts for displays in embedded, SDL, or terminal environments. It is built to be small, fast, and easy to drop into projects with minimal effort. The library ships as a single, self-contained header and a font data set that you can embed directly into your firmware or application. It avoids dependencies, keeps footprint small, and prioritizes clarity and portability across microcontrollers, SBCs, and desktop development workstations.

If you want the latest stable assets or binaries, check the Releases page. The page houses the downloadable assets and release notes you need to run the library on your target platform. You can visit the Releases page using the link above, or click the badge to jump straight there when you need to grab a build or font data. This approach keeps the library lean while giving you full control over what you deploy to your device.

Table of contents
- Why ascii-render
- Core design and philosophy
- Quick start: what you need
- Platform coverage
- API overview
- Font data and formats
- Rendering workflow
- Examples: tiny programs to get you started
- SDL usage example
- Arduino and embedded usage
- ESP32 and ESP-family targets
- STM32 and ARM Cortex-M targets
- Raspberry Pi and Linux/macOS hosts
- Memory usage and optimizations
- Font creation and conversion tools
- Debugging tips
- Testing and CI
- Contributing
- FAQ
- License
- Credits

Why ascii-render
- Lightweight and portable: This library is header-only, which means you can drop it into nearly any C project without building a separate library. No linking overhead, no extra dependencies, and no odd build steps.
- Low memory footprint: The rendering model uses compact glyph bitmaps and a simple, predictable framebuffer layout. It is designed for devices with tight RAM constraints and limited flash storage.
- Cross-platform friendliness: It targets embedded boards, desktop environments via SDL, and even terminal emulators. The same API and font data work across platforms with minimal adaptation.
- Clear API and data formats: The library focuses on readability and straightforward integration. Font glyphs are stored as compact bitmaps, and rendering routines map those bitmaps into a framebuffer bound to your display or output surface.
- No-dependency promise: The header is self-contained. You do not pull in external font engines or graphics pipelines. You control how the data gets displayed on your chosen medium.
- Open and extensible: The design anticipates extension. You can provide your own framebuffer, swap in your own glyph metrics, or switch between monospaced and proportional layouts with a small amount of glue code.

Core design and philosophy
- Simplicity first: The library favors simple interfaces. The goal is to make it easy to render text quickly and predictably on tiny boards, without a complex rendering stack.
- Explicit memory usage: You know exactly how much RAM is used, because glyphs are stored in fixed-size bitmaps and the framebuffer is user-managed.
- Deterministic performance: Rendering a line of text takes a fixed amount of time proportional to the number of characters. There are no hidden caches or expensive lookups.
- Deterministic output: The glyph grid and the rendering scale stay predictable. This helps avoid jitter and misalignment on small displays.
- Platform-agnostic rendering: The library does not assume a particular display driver. It writes to a provided framebuffer, letting you drive any display technologies you want—LCD, OLED, TFT, or textual terminals.

Quick start: what you need
- A C compiler with robust support for header inclusions (GCC is a solid default; Clang works well too).
- A target platform where you can allocate or manage a framebuffer.
- The ascii-render header and a font data set. The header is all you need to render simple ASCII text.
- A display or output medium to visualize the framebuffer, such as:
  - An LCD or OLED module connected to a microcontroller.
  - An SDL window on a desktop environment for testing and demonstration.
  - A terminal emulator that can render a monochrome or mapped bitmap area.
- Optional: a font asset set in a simple bitmap format that matches the library’s expectations (bitmaps per glyph with a consistent width and height).

Platform coverage
- Embedded microcontrollers: Works well on tiny systems with constrained RAM, flash, and CPU time. Examples include AVR, SAM, ESP32, STM32, and similar devices.
- ESP32 family: The library’s lack of dependencies makes it a good match for ESP-IDF projects. It plays nicely with the usual FreeRTOS-based flow.
- STM32 and ARM Cortex-M: The header-only approach reduces complexity. You can include the header in your projects and render text to your peripherals.
- Arduino: The library integrates with the standard Arduino toolchain. You can drop the header into your sketch and render text to a small display.
- Raspberry Pi and Linux/macOS hosts: Use SDL or a simple framebuffer to debug and prototype. It’s ideal for quick iterations and UI proof of concept.
- Text-based terminals: For fun and testing, you can render to a character-based terminal that supports direct framebuffer-like output or to a small off-screen buffer and dump the results.

API overview
- ascii_font_t
  - Represents a font. Holds metrics such as glyph width, glyph height, baseline, and mapping from ASCII code to glyph bitmap.
- ascii_font_create_from_bitmap(const uint8_t* bitmap, size_t glyph_width, size_t glyph_height)
  - Create a font from a raw bitmap array. This is useful when you generate font data with an external tool and want to wrap it in the library.
- ascii_render_context_t
  - Holds the target framebuffer, its width and height, and color information if you render to a colored framebuffer.
- ascii_render_text(ascii_font_t*, const char* text, int x, int y, uint8_t* fb, int fb_w, int fb_h, uint8_t fg, uint8_t bg)
  - Render a string into the framebuffer at a given position.
  - fg and bg specify the foreground and background color indices (or grayscale values) if your display supports it.
- ascii_render_char(ascii_font_t*, char c, int x, int y, uint8_t* fb, int fb_w, int fb_h, uint8_t fg, uint8_t bg)
  - Render a single character with the same conventions as text rendering.
- ascii_font_destroy(ascii_font_t*)
  - Free any resources tied to a font (if your platform allocates memory for font metadata; often this is a no-op for header-only designs).
- Font formats
  - 8x8, 8x12, 8x16, 8x8x? (bitmap-based glyphs)
  - Each glyph is a small bitmap with a fixed width and height, stored in row-major order.
  - The font data maps ASCII codes to glyph bitmaps. Unsupported characters can map to a blank glyph.
- Rendering workflow
  - Load or define a font data set.
  - Allocate or define a framebuffer for your target display.
  - Call ascii_render_text or ascii_render_char to paint glyphs into the framebuffer.
  - Transfer the framebuffer to the display hardware or rendering surface (SDL, terminal, or pixel buffer).
  - Update the display as needed.

Font data and formats
- Font data is a compact array of bitmaps. Each glyph is represented by a fixed-sized block of bytes, where each bit corresponds to a pixel in the glyph.
- A typical 8x8 font stores 8 bytes per glyph, one byte per row. A glyph grid can be a simple 256-entry table for the full ASCII range (0-127 or 0-255, depending on your font).
- The header defines a font object that includes:
  - Glyph width and height
  - A pointer to the bitmap glyph array
  - A mapping table for ASCII codes to glyph indices
- Generating font data
  - Tools exist to convert bitmap fonts to C arrays. You can use font editors that export to a C array, or write a small converter that reads a font image and outputs a column-major or row-major bitmap per glyph.
  - Aim for consistency: maintain the same glyph width and height across all glyphs used by your target language set.
- Choosing a font
  - For embedded projects, 5x7 or 6x8 fonts are very common and provide a good balance between legibility and footprint.
  - For SDL or desktop prototypes, you can choose slightly larger glyphs (8x8, 8x12, 8x16) to test readability on larger windows.

Rendering workflow: a step-by-step guide
- Step 1: Pick a font data set
  - Choose a font with glyphs stored as fixed-size bitmaps.
  - Ensure the font includes the ASCII range you need (space to ~Z and punctuation).
- Step 2: Create or load the font in your project
  - Use ascii_font_create_from_bitmap if you have a raw bitmap font.
  - Or wrap an existing font data array into the font structure expected by the library.
- Step 3: Prepare the framebuffer
  - Allocate a buffer that matches the target display’s pixel layout.
  - Decide whether you render in monochrome, grayscale, or color, depending on your hardware.
  - If you drive a monochrome display, you might compress the framebuffer to save memory.
- Step 4: Render text
  - Call ascii_render_text with your font, the string you want to display, and the coordinates on the framebuffer.
  - If you render to a color framebuffer, decide how you map glyph bits to color values.
- Step 5: Update the display
  - Send the framebuffer to your display or surface.
  - If you are using SDL for testing, you can render the framebuffer to a window and observe changes in real time.
- Step 6: Iterate
  - Test different font sizes, alignments, and string lengths.
  - Measure RAM usage and execution time to ensure you stay within limits.

Examples: tiny programs to get you started
- Minimal C usage (no external dependencies)
  - This example demonstrates including the header and rendering a short string to a small monochrome buffer.
  - It assumes an 80x25 character grid, 8x8 font metrics, and a simple monochrome framebuffer.

Code example 1: simple text to a monochrome buffer
```c
#include "ascii_render.h"
#include <stdint.h>
#include <string.h>

#define FB_W 80
#define FB_H 25

// A tiny 8x8 font data set (placeholder data)
extern const uint8_t font8x8_bitmap[]; // your real font data here

int main(void) {
    // Create font from bitmap data
    ascii_font_t* font = ascii_font_create_from_bitmap(font8x8_bitmap, 8, 8);

    // Simple monochrome framebuffer: 1 byte per pixel for simplicity here
    uint8_t fb[FB_W * FB_H];
    memset(fb, 0, sizeof(fb));

    // Render text at position (0,0)
    const char* text = "HELLO ASCII";
    ascii_render_text(font, text, 0, 0, fb, FB_W, FB_H, 1, 0);

    // At this point, you would copy fb to your display hardware
    // For testing, you could print a representation to a terminal or render with SDL.

    // Clean up
    ascii_font_destroy(font);
    return 0;
}
```

Code example 2: SDL-based display for testing on a desktop
```c
#include "ascii_render.h"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define FB_W 320
#define FB_H 240

extern const uint8_t font8x8_bitmap[];

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("ascii-render SDL Test",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_DEFINED,
                                       FB_W, FB_H,
                                       0);
    if (!win) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* tex = SDL_CreateTexture(ren,
                                         SDL_PIXELFORMAT_RGB888,
                                         SDL_TEXTUREACCESS_STREAMING,
                                         FB_W, FB_H);

    ascii_font_t* font = ascii_font_create_from_bitmap(font8x8_bitmap, 8, 8);
    uint8_t fb[FB_W * FB_H];
    memset(fb, 0, sizeof(fb));

    const char* text = "HELLO SDL ASCII";
    ascii_render_text(font, text, 0, 0, fb, FB_W, FB_H, 0xFF, 0x00);

    // Copy framebuffer to texture
    SDL_UpdateTexture(tex, NULL, fb, FB_W * 4);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    ascii_font_destroy(font);
    return 0;
}
```

Code example 3: Arduino-style usage (pseudo-code)
```c
#include "ascii_render.h"
#include <Arduino.h>

#define WIDTH 128
#define HEIGHT 64

extern const uint8_t font8x8_bitmap[];

ascii_font_t* g_font;
uint8_t g_fb[WIDTH * HEIGHT];

void setup() {
  Serial.begin(115200);
  g_font = ascii_font_create_from_bitmap(font8x8_bitmap, 8, 8);
  memset(g_fb, 0, sizeof(g_fb));

  ascii_render_text(g_font, "ARDUINO ASCII", 0, 0, g_fb, WIDTH, HEIGHT, 1, 0);

  // Here, send g_fb to your display driver (e.g., SPI, I2C) for the 128x64 display.
}

void loop() {
  // Keep running or update text as needed.
}
```

SDL and host testing
- Using SDL for test builds gives you rapid feedback without needing hardware.
- It also makes it easy to compare how glyphs render at different font sizes and bit depths.
- When using SDL, render the framebuffer to a texture and present it in a window. This approach mirrors how a real display would consume the data.

Arduino and embedded usage
- The header-only approach helps you minimize RAM usage. Place the font bitmap data in flash and reference it via the font loader.
- On microcontrollers with limited RAM, consider rendering directly to the display row by row to avoid building large framebuffers in RAM.
- Use PROGMEM (on AVR-based boards) or equivalent attributes to keep font data in flash, not RAM, when possible.
- Keep an eye on interrupt-driven tasks; rendering can be time-sensitive on busy systems. Structure rendering to happen in idle periods or within a predictable loop.

ESP32 and ESP-family targets
- ESP32 is capable of running the library with SDL-like debugging on the desktop and actual display rendering on the chip.
- For ESP-IDF projects, you can wrap the header-in-a-project approach with your display driver, using a small memory pool for font data if you want to keep flash usage predictable.
- Since the library is header-only and dependency-light, you can keep your code compact and clean, which helps in the constrained ESP32 environment.

STM32 and ARM Cortex-M targets
- On STM32, you typically write frames to an LCD or OLED display using a driver (SPI or parallel interface). The ascii-render API remains the same; you only need a framebuffer mapped to your display’s memory.
- The approach stays consistent: select a font, render text into a framebuffer, and push the framebuffer to the display with your driver code.

Raspberry Pi and Linux/macOS hosts
- On a Raspberry Pi or desktop Linux/macOS system, SDL makes it straightforward to prototype rendering. You can reuse the same code paths you use on microcontrollers, then port to the actual hardware by changing the framebuffer sink.
- The goal is to reduce the gap between prototype and production. Start with SDL, then transition to hardware with minimal changes.

Memory usage and optimizations
- Font data footprint: A fixed-size glyph bitmap per character. The total font size is glyph_width * glyph_height * number_of_glyphs. Choose a font that balances readability and memory usage for your device.
- Framebuffer footprint: The framebuffer size is width * height * bytes_per_pixel. On color displays, you’ll multiply memory usage by bytes_per_pixel (for example, 2 for 16-bit color or 3 for 24-bit). On monochrome displays, you might pack pixels to 1 bit per pixel to save RAM.
- Rendering time: Rendering a line of text scales with the number of characters and the glyph size. With a simple bit-per-pixel operation, you can achieve predictable rendering times, suitable for microcontroller loops.
- Font choice and layout: If you need more text per line, use a smaller font. If you need richer punctuation, extend the font with extra glyphs. Always test under memory constraints to avoid overflows.

Font creation and conversion tools
- Font generators and converters
  - Several tools convert bitmap fonts to C-style glyph arrays. Choose a tool that produces glyph bitmaps with consistent row widths.
  - Keep a consistent data format so you can swap fonts without changing the rendering code.
- Font design considerations
  - Legibility matters more than extreme detail on small displays. Favor clean, high-contrast glyphs.
  - Include common punctuation and a small set of extended ASCII characters if your application requires it.
  - Consider including a blank glyph as a fallback for unknown characters.
- Sample workflow
  - Design a font in a bitmap editor with a fixed grid (e.g., 8x8 or 8x12).
  - Export to a raw bitmap or a C array using a converter.
  - Integrate the array into your project and wrap it with ascii_font_create_from_bitmap.
  - Test rendering quality across the characters you plan to show.

Debugging tips
- Validate font loading: Ensure the font object is properly created and that the glyph dimensions match the font bitmap data.
- Validate framebuffer integrity: On every render, check a small region of the framebuffer to ensure the bits map to expected pixels.
- Visual checks: When using SDL or a real display, test with simple text first (e.g., "ABC123") before moving to full strings with punctuation.
- Edge cases:
  - Characters outside the ASCII range should map to a blank glyph.
  - Strings with null terminators must be handled gracefully, without reading beyond the string end.
  - Very long strings should wrap or be truncated depending on your design.

Testing and CI
- Unit tests
  - Create tests for glyph rendering consistency by comparing a rendered framebuffer against a known-good bitmap snapshot.
  - Test boundary cases: first and last ASCII character, space, and punctuation.
- Cross-platform tests
  - Build tests for at least two targets: a microcontroller-like environment and a desktop environment with SDL.
  - Verify that rendering outcomes are consistent across platforms, or document platform-specific differences.
- Continuous integration
  - Use a lightweight CI workflow to compile the header and run a minimal test suite on multiple platforms.
  - Ensure the CI configuration remains simple to avoid noisy failures due to platform quirks.

Contributing
- How to contribute
  - Fork the repository and create a feature branch for your change.
  - Implement your change in a self-contained way. Include a small test or example that demonstrates the new capability.
  - Write clear code comments. Keep functions small and focused.
  - Update the README with usage notes if your change affects the public API or common usage patterns.
- Coding style
  - Use clear, direct language in code and comments.
  - Prefer straightforward logic over clever optimizations that reduce readability.
  - Keep lines reasonably short and document any tricky parts.
- Documentation
  - Add examples that illustrate how to integrate with a specific platform.
  - Document any new API surfaces with simple, copy-pastable code.
- Licensing
  - The project uses a permissive license to enable broad use in embedded and educational contexts.
  - If you add code from external sources, ensure you comply with their licenses.

FAQ
- Is ascii-render truly header-only?
  - Yes. The core library is delivered as a single header. It does not require compiling a separate library.
- Can I use it on a small 8-bit microcontroller?
  - Yes. It is designed with small memory footprints in mind. Use a font size that fits your RAM and display resolution.
- Do I need SDL to run it on a PC?
  - No. SDL is optional for testing. You can render to a custom framebuffer or write small tests that don’t require a display driver.
- How do I add a new font?
  - Prepare a fixed-size bitmap per glyph and wrap it with the provided font creation function. Then use the new font with the render routines.
- Are there any dependencies?
  - None required for the header. If you want to test with SDL, you’ll need to install SDL2 on your host system.

License
- This project is released under a permissive license. See the LICENSE file for details.
- The license covers use in commercial and non-commercial projects. It also allows you to adapt and redistribute the code with minimal restrictions.

Credits
- Maintainer and primary author: shahzaib739
- Special thanks to contributors who provided font data, tests, or improvements to the rendering pipeline.
- If you use ascii-render in your project, a small attribution in your documentation is appreciated but not required.

Topics
- arduino
- ascii
- c-library
- display
- embedded
- embedded-systems
- esp32
- font
- header-only
- lcd
- lightweight
- low-memory
- low-resource
- microcontroller
- no-dependencies
- oled
- raspberry-pi
- stm32
- text-rendering
- tft

Releases
- For the latest binaries and font bundles, visit the Releases page linked at the top. The page contains release notes and asset files you can download, then execute per the instructions in the release notes. If you need to grab the files, head to the Releases section using the link provided. You can also click the badge above to navigate quickly.

Note: If you want to see more examples, a fuller API reference, and additional fonts, you can explore more extensive sample code and fonts in the repository’s assets or in the Releases section. The Releases page is the primary source of downloadable material and recommended starting point for any new project using ascii-render.

Images and visuals
- Preview image: A simple ASCII font rendering preview is shown in the project’s assets. For a live demonstration, you can also run the SDL test example to visualize how ASCII glyphs map to a framebuffer.
- Preview banners
  - ASCII art banner: A stylized representation of ascii-render in a terminal-friendly font.
  - Font sheet sample: A small bitmap showing how a font matrix is laid out for 8x8 glyphs.

Additional notes
- The library’s header is designed to be easy to read and modify. If you need to extend the rendering for grayscale or color glyphs, you can layer your own color map on top of the existing monochrome bitmaps with small helper routines.
- For people who want to customize the font more deeply, consider exporting the font glyphs to additional sizes and widths. You can provide a few font variants (e.g., 6x8, 8x8, 8x12) and switch between them with a simple font selector in your application code.

This README intentionally provides a broad, practical view of ascii-render. It aims to help you integrate the library into a wide range of environments—from tiny microcontrollers to desktop testing—with an eye toward clarity, portability, and low resource usage. The goal is to support developers who want reliable ASCII text rendering without the overhead of a large font engine. The Releases page contains the latest official assets and notes to guide you through obtaining, building, and deploying ascii-render on your chosen platform. Visit the page to download and run the appropriate release for your device.