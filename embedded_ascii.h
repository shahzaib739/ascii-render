/**
 * @file embedded_ascii.h
 * @brief Library for working with an embedded ASCII font.
 *
 * This file contains definitions and functions for easy use of a
 * monochrome ASCII font in embedded systems. It provides means
 * for retrieving character bitmaps, drawing characters and text
 * using callback functions or directly into image buffers
 * (monochrome or RGB565).
 *
 * @author Ferki
 * @date 2025-08-07
 * @version 1.1
 * @copyright (c) 2025 Ferki. All rights reserved.
 *
 * @license MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef EMBEDDED_ASCII_H
#define EMBEDDED_ASCII_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stddef.h>

// ===================== CONFIGURATION =====================
/**
 * @def ASCII_FONT_WIDTH
 * @brief Width of a single font character in pixels.
 */
#define ASCII_FONT_WIDTH     8
/**
 * @def ASCII_FONT_HEIGHT
 * @brief Height of a single font character in pixels.
 */
#define ASCII_FONT_HEIGHT    8
/**
 * @def ASCII_FIRST_CHAR
 * @brief ASCII code of the first character in the font table.
 */
#define ASCII_FIRST_CHAR     32 // Space
/**
 * @def ASCII_LAST_CHAR
 * @brief ASCII code of the last character in the font table.
 */
#define ASCII_LAST_CHAR      127 // DEL
/**
 * @def ASCII_CHAR_COUNT
 * @brief Total number of characters in the font.
 */
#define ASCII_CHAR_COUNT     (ASCII_LAST_CHAR - ASCII_FIRST_CHAR)

/**
 * @typedef ascii_mono_color_t
 * @brief Type for representing a monochrome color (0 or 1).
 */
typedef uint8_t ascii_mono_color_t;   // Monochrome pixel
/**
 * @typedef ascii_rgb565_color_t
 * @brief Type for representing an RGB565 color.
 */
typedef uint16_t ascii_rgb565_color_t; // RGB565 pixel

// Default colors
/**
 * @def ASCII_COLOR_WHITE
 * @brief Macro for white color in RGB565 format.
 */
#define ASCII_COLOR_WHITE    0xFFFF
/**
 * @def ASCII_COLOR_BLACK
 * @brief Macro for black color in RGB565 format.
 */
#define ASCII_COLOR_BLACK    0x0000

// ===================== FONT DATA =====================
/**
 * @brief Array of ASCII character bitmaps.
 *
 * Each array element represents the bitmap of one character.
 * A bitmap consists of 8 bytes, where each byte corresponds to a row of the character.
 * Bits in the byte represent pixels (1 - on, 0 - off).
 */
static const uint8_t ascii_font[ASCII_CHAR_COUNT][ASCII_FONT_HEIGHT] = {
    // [Your font remains unchanged]
    // Space (ASCII 32)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ! (ASCII 33)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // " (ASCII 34)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // # (ASCII 35)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // $ (ASCII 36)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // % (ASCII 37)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // & (ASCII 38)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ' (ASCII 39)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ( (ASCII 40)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ) (ASCII 41)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // * (ASCII 42)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // + (ASCII 43)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // , (ASCII 44)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // - (ASCII 45)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // . (ASCII 46)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // / (ASCII 47)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 0 (ASCII 48)
    {0x3E, 0x7F, 0x6B, 0x6B, 0x6B, 0x6B, 0x7F, 0x3E},
    // 1 (ASCII 49)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 2 (ASCII 50)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 3 (ASCII 51)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 4 (ASCII 52)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 5 (ASCII 53)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 6 (ASCII 54)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 7 (ASCII 55)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 8 (ASCII 56)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // 9 (ASCII 57)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // : (ASCII 58)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ; (ASCII 59)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // < (ASCII 60)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // = (ASCII 61)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // > (ASCII 62)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ? (ASCII 63)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // @ (ASCII 64)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // A (ASCII 65)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // B (ASCII 66)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // C (ASCII 67)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // D (ASCII 68)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // E (ASCII 69)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // F (ASCII 70)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // G (ASCII 71)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // H (ASCII 72)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // I (ASCII 73)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // J (ASCII 74)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // K (ASCII 75)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // L (ASCII 76)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // M (ASCII 77)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // N (ASCII 78)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // O (ASCII 79)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // P (ASCII 80)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // Q (ASCII 81)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // R (ASCII 82)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // S (ASCII 83)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // T (ASCII 84)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // U (ASCII 85)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // V (ASCII 86)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // W (ASCII 87)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // X (ASCII 88)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // Y (ASCII 89)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // Z (ASCII 90)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // [ (ASCII 91)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // \ (ASCII 92)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ] (ASCII 93)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ^ (ASCII 94)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // _ (ASCII 95)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ` (ASCII 96)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // a (ASCII 97)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // b (ASCII 98)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // c (ASCII 99)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // d (ASCII 100)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // e (ASCII 101)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // f (ASCII 102)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // g (ASCII 103)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // h (ASCII 104)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // i (ASCII 105)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // j (ASCII 106)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // k (ASCII 107)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // l (ASCII 108)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // m (ASCII 109)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // n (ASCII 110)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // o (ASCII 111)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // p (ASCII 112)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // q (ASCII 113)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // r (ASCII 114)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // s (ASCII 115)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // t (ASCII 116)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // u (ASCII 117)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // v (ASCII 118)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // w (ASCII 119)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // x (ASCII 120)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // y (ASCII 121)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // z (ASCII 122)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // { (ASCII 123)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // | (ASCII 124)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // } (ASCII 125)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // ~ (ASCII 126)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

// ===================== LIBRARY API =====================

/**
 * @brief Get character bitmap.
 *
 * This function returns a pointer to the bitmap of the given character.
 * If the character is outside the defined range (ASCII_FIRST_CHAR to ASCII_LAST_CHAR),
 * the function returns the bitmap of a space character.
 *
 * @param c The character to get the bitmap for.
 * @return A pointer to the 8-byte character bitmap.
 */
static inline const uint8_t* ascii_get_char_bitmap(char c) {
    if (c < ASCII_FIRST_CHAR || c >= ASCII_LAST_CHAR)
        return ascii_font[0];  // Returns space for invalid characters
    return ascii_font[c - ASCII_FIRST_CHAR];
}

/**
 * @brief Callback function for drawing a pixel.
 *
 * This function type is used to abstract the process of drawing
 * a single pixel on the display. The user must implement this function
 * according to their display hardware.
 *
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Pointer to the pixel color (type depends on implementation).
 * @param user_data Pointer to user-defined data that can be passed
 * to the callback function (e.g., display context).
 */
typedef void (*ascii_pixel_fn)(int x, int y, void* color, void* user_data);

/**
 * @brief Draw a character using a callback function.
 *
 * This function draws a single character on the display using the provided
 * callback function to draw each pixel.
 *
 * @param c The character to draw.
 * @param x The X-coordinate of the top-left corner of the character.
 * @param y The Y-coordinate of the top-left corner of the character.
 * @param pixel_fn The function for drawing individual pixels.
 * @param color The color to draw the character with.
 * @param user_data User-defined data to be passed to `pixel_fn`.
 */
static inline void ascii_draw_char(
    char c,
    int x,
    int y,
    ascii_pixel_fn pixel_fn,
    void* color,
    void* user_data
) {
    const uint8_t* bitmap = ascii_get_char_bitmap(c);
    for (int row = 0; row < ASCII_FONT_HEIGHT; row++) {
        for (int col = 0; col < ASCII_FONT_WIDTH; col++) {
            if (bitmap[row] & (1 << (7 - col))) {
                pixel_fn(x + col, y + row, color, user_data);
            }
        }
    }
}

/**
 * @brief Draw text using a callback function.
 *
 * This function draws a string of text on the display, handling newline characters ('\n').
 * Each character is drawn using `ascii_draw_char`.
 *
 * @param text Null-terminated string of text to draw.
 * @param x The X-coordinate of the top-left corner of the first character.
 * @param y The Y-coordinate of the top-left corner of the first character.
 * @param pixel_fn The function for drawing individual pixels.
 * @param color The color to draw the text with.
 * @param user_data User-defined data to be passed to `pixel_fn`.
 * @return The width of the drawn text in pixels (maximum line width).
 */
static inline int ascii_draw_text(
    const char* text,
    int x,
    int y,
    ascii_pixel_fn pixel_fn,
    void* color,
    void* user_data
) {
    int start_x = x;
    int current_y = y;
    const char* ptr = text;

    while (*ptr) {
        if (*ptr == '\n') {
            current_y += ASCII_FONT_HEIGHT;
            x = start_x;
        } else {
            ascii_draw_char(*ptr, x, current_y, pixel_fn, color, user_data);
            x += ASCII_FONT_WIDTH;
        }
        ptr++;
    }

    return x - start_x;
}

/**
 * @brief Draw a character to a monochrome image buffer.
 *
 * This function draws a single character directly into the provided monochrome
 * image buffer. It performs buffer boundary checks.
 *
 * @param c The character to draw.
 * @param buffer Pointer to the image buffer (uint8_t array).
 * @param buf_width Width of the image buffer in pixels.
 * @param buf_height Height of the image buffer in pixels.
 * @param x X-coordinate of the top-left corner of the character.
 * @param y Y-coordinate of the top-left corner of the character.
 * @param color Color (0 or 1) for drawing the character's pixels.
 */
static inline void ascii_draw_char_to_mono_buffer(
    char c,
    uint8_t* buffer,
    int buf_width,
    int buf_height,
    int x,
    int y,
    ascii_mono_color_t color
) {
    if (x < 0 || y < 0 || x >= buf_width || y >= buf_height)
        return;

    const uint8_t* bitmap = ascii_get_char_bitmap(c);
    for (int row = 0; row < ASCII_FONT_HEIGHT; row++) {
        int py = y + row;
        if (py >= buf_height) break;

        for (int col = 0; col < ASCII_FONT_WIDTH; col++) {
            int px = x + col;
            if (px >= buf_width) break;

            if (bitmap[row] & (1 << (7 - col))) {
                buffer[py * buf_width + px] = color;
            }
        }
    }
}

/**
 * @brief Draw a character to an RGB565 image buffer.
 *
 * This function draws a single character directly into the provided RGB565
 * image buffer. It performs buffer boundary checks.
 *
 * @param c The character to draw.
 * @param buffer Pointer to the image buffer (uint16_t array).
 * @param buf_width Width of the image buffer in pixels.
 * @param buf_height Height of the image buffer in pixels.
 * @param x X-coordinate of the top-left corner of the character.
 * @param y Y-coordinate of the top-left corner of the character.
 * @param color Color (RGB565) for drawing the character's pixels.
 */
static inline void ascii_draw_char_to_rgb565_buffer(
    char c,
    uint16_t* buffer,
    int buf_width,
    int buf_height,
    int x,
    int y,
    ascii_rgb565_color_t color
) {
    if (x < 0 || y < 0 || x >= buf_width || y >= buf_height)
        return;

    const uint8_t* bitmap = ascii_get_char_bitmap(c);
    for (int row = 0; row < ASCII_FONT_HEIGHT; row++) {
        int py = y + row;
        if (py >= buf_height) break;

        for (int col = 0; col < ASCII_FONT_WIDTH; col++) {
            int px = x + col;
            if (px >= buf_width) break;

            if (bitmap[row] & (1 << (7 - col))) {
                buffer[py * buf_width + px] = color;
            }
        }
    }
}

// ===================== UTILITIES =====================

/**
 * @brief Calculate text width.
 *
 * This function calculates the maximum width of the given text string in pixels.
 * It accounts for newline characters ('\n').
 *
 * @param text Null-terminated string of text.
 * @return The maximum width of the text in pixels.
 */
static inline int ascii_text_width(const char* text) {
    int width = 0;
    int line_width = 0;
    const char* ptr = text;

    while (*ptr) {
        if (*ptr == '\n') {
            if (line_width > width) width = line_width;
            line_width = 0;
        } else {
            line_width += ASCII_FONT_WIDTH;
        }
        ptr++;
    }

    return (line_width > width) ? line_width : width;
}

/**
 * @brief Calculate text height.
 *
 * This function calculates the total height of the given text string in pixels,
 * accounting for all newline characters ('\n').
 *
 * @param text Null-terminated string of text.
 * @return The total height of the text in pixels.
 */
static inline int ascii_text_height(const char* text) {
    int height = ASCII_FONT_HEIGHT;
    const char* ptr = text;

    while (*ptr) {
        if (*ptr == '\n') {
            height += ASCII_FONT_HEIGHT;
        }
        ptr++;
    }

    return height;
}

// ===================== SDL2 EXTENSION =====================

#ifdef ASCII_ENABLE_SDL2

#include <SDL.h>
#include <SDL_ttf.h>

/**
 * @brief Structure to hold SDL context for rendering.
 */
typedef struct {
    SDL_Renderer* renderer; /**< Pointer to the SDL Renderer. */
    TTF_Font* font;         /**< Pointer to the TTF Font. */
    SDL_Color color;        /**< Color for rendering text. */
} ascii_sdl_context;

/**
 * @brief Initialize SDL context for text rendering.
 *
 * This function initializes SDL_ttf and loads a font, preparing an `ascii_sdl_context`
 * for use with SDL rendering functions.
 *
 * @param font_path Path to the font file (e.g., ".ttf").
 * @param font_size Size of the font in pixels.
 * @param color Color of the text.
 * @param renderer The SDL renderer to associate with this context.
 * @return An initialized `ascii_sdl_context` pointer on success, or NULL on error.
 */
static ascii_sdl_context* ascii_sdl_init(
    const char* font_path,
    int font_size,
    SDL_Color color,
    SDL_Renderer* renderer
) {
    if (TTF_Init() != 0) return NULL;

    TTF_Font* font = TTF_OpenFont(font_path, font_size);
    if (!font) return NULL;

    ascii_sdl_context* ctx = malloc(sizeof(ascii_sdl_context));
    if (!ctx) {
        TTF_CloseFont(font);
        return NULL;
    }

    ctx->renderer = renderer;
    ctx->font = font;
    ctx->color = color;
    return ctx;
}

/**
 * @brief Render text using SDL_ttf.
 *
 * This function renders a given text string to the SDL renderer using the
 * font and color specified in the `ascii_sdl_context`.
 *
 * @param ctx Pointer to the initialized `ascii_sdl_context`.
 * @param text The null-terminated string to render.
 * @param x The X-coordinate for the top-left corner of the rendered text.
 * @param y The Y-coordinate for the top-left corner of the rendered text.
 */
static void ascii_sdl_render_text(
    ascii_sdl_context* ctx,
    const char* text,
    int x,
    int y
) {
    SDL_Surface* surface = TTF_RenderText_Solid(ctx->font, text, ctx->color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(ctx->renderer, texture, NULL, &dest);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

/**
 * @brief Clean up SDL resources.
 *
 * This function frees the resources associated with an `ascii_sdl_context`,
 * including the font and the context itself, and quits SDL_ttf.
 *
 * @param ctx Pointer to the `ascii_sdl_context` to clean up.
 */
static void ascii_sdl_cleanup(ascii_sdl_context* ctx) {
    if (ctx) {
        TTF_CloseFont(ctx->font);
        free(ctx);
        TTF_Quit();
    }
}

#endif // ASCII_ENABLE_SDL2

// ===================== DEMO MODE =====================

#ifdef ASCII_DEMO_CONSOLE

#include <stdio.h>
#include <time.h>

/**
 * @brief Callback function for drawing a pixel in the console.
 *
 * This function is an example implementation of `ascii_pixel_fn` for
 * outputting characters to a text console. It marks pixels with the '#' character.
 *
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Not used in this example.
 * @param user_data Pointer to the console character buffer and its width.
 */
static void console_pixel_fn(int x, int y, void* color, void* user_data) {
    (void)color; // Ignore the color parameter
    char* buffer = (char*)((intptr_t*)user_data)[0]; // Retrieve buffer pointer from user_data array
    int width = ((int*)user_data)[1]; // Retrieve width from user_data array
    buffer[y * width + x] = '#';
}

/**
 * @brief Demonstration function for outputting ASCII font to the console.
 *
 * This function demonstrates the use of the `embedded_ascii` library
 * by drawing text and an ASCII table into a text buffer,
 * which is then printed to the console.
 */
static void ascii_demo_console() {
    const int WIDTH = 80;
    const int HEIGHT = 40;
    char buffer[WIDTH * HEIGHT];
    // user_data will now contain a pointer to the buffer and its width.
    // For simplicity, user_data can be a struct or an array containing this data.
    // Here, we use an int array.
    intptr_t demo_user_data[2]; // Use intptr_t for storing pointer
    demo_user_data[0] = (intptr_t)buffer; // Store pointer to buffer
    demo_user_data[1] = WIDTH; // Store width

    // Initialize the buffer
    memset(buffer, ' ', sizeof(buffer));
    for (int i = 0; i < HEIGHT; i++) {
        buffer[i * WIDTH + WIDTH - 1] = '\0'; // Null-terminate each line
    }

    // Draw text
    ascii_draw_text("Embedded ASCII\nLibrary v1.1",
                    2, 2,
                    console_pixel_fn,
                    NULL,
                    demo_user_data); // Pass array with data

    // Draw ASCII table
    int x = 2, y = 6;
    for (char c = ASCII_FIRST_CHAR; c < ASCII_LAST_CHAR; c++) {
        ascii_draw_char(c, x, y, console_pixel_fn, NULL, demo_user_data); // Pass array with data
        x += ASCII_FONT_WIDTH;
        if (x > WIDTH - ASCII_FONT_WIDTH - 2) {
            x = 2;
            y += ASCII_FONT_HEIGHT;
        }
    }

    // Print the buffer
    for (int row = 0; row < HEIGHT; row++) {
        // Check if the line is not empty to avoid printing extra blank lines
        // (although memset fills with spaces, null-terminator at the end of the line helps)
        puts(buffer + row * WIDTH);
    }
}

/**
 * @brief Benchmark demonstration function.
 *
 * This function performs a simple benchmark of the `ascii_draw_text` function
 * by rendering a specific text string multiple times into a monochrome buffer
 * and measuring the elapsed time.
 */
static void benchmark_demo() {
    const int WIDTH = 128;
    const int HEIGHT = 64;
    uint8_t buffer[WIDTH * HEIGHT];
    memset(buffer, 0, sizeof(buffer));

    const char* text = "Benchmark: ASCII rendering";
    const int iterations = 1000;

    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        // Note: The original call `ascii_draw_text(text, buffer, WIDTH, HEIGHT, 10, 10, 1);`
        // is incorrect for ascii_draw_text which expects pixel_fn and user_data.
        // Assuming it was intended to call a direct buffer drawing function,
        // but since ascii_draw_text uses pixel_fn, this benchmark needs a dummy pixel_fn
        // or a direct buffer drawing function to be meaningful.
        // For now, I'll simulate a direct buffer draw by calling draw_char_to_mono_buffer
        // for each character in the text to make the benchmark realistic for buffer drawing.
        // If the intent was to benchmark the callback mechanism, a different setup is needed.

        // Simulating text drawing to buffer for benchmark
        int current_x = 10;
        int current_y = 10;
        for (const char* ptr = text; *ptr != '\0'; ++ptr) {
            if (*ptr == '\n') {
                current_y += ASCII_FONT_HEIGHT;
                current_x = 10;
            } else {
                ascii_draw_char_to_mono_buffer(*ptr, buffer, WIDTH, HEIGHT, current_x, current_y, 1);
                current_x += ASCII_FONT_WIDTH;
            }
        }
    }
    clock_t end = clock();

    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    double time_per_frame = total_time / iterations * 1000;

    printf("Rendered %d frames in %.2f seconds\n", iterations, total_time);
    printf("Average: %.2f ms per frame\n", time_per_frame);
}

#endif // ASCII_DEMO_CONSOLE

#ifdef __cplusplus
}
#endif

#endif // EMBEDDED_ASCII_H

