#pragma once

// a few color defines to use for now
// gonna change in the future, maybe to a new header
#define RED 0xFF0000FF
#define CYAN 0x1AA1AA1E

#include <SDL3/SDL_video.h>
#include <cstdint>

struct Color 
{
    uint32_t r, g, b;
};

struct Framebuffer 
{
    void drawPixel(int x, int y, Color cl);
    void clearScreen(Color cl);
    void clearScreen(uint32_t cl);
    // writes data from framebuffer to streaming texture
    void write(void* texture_pixels, int texture_pitch);

    Framebuffer() = delete;
    Framebuffer(int winWidth, int winHeight);
    ~Framebuffer();

    int width;
    int height;
    int pitch;        // distance in bytes between rows of pixels
    uint32_t* pixels;
};

