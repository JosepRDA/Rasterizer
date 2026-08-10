#pragma once

#include <SDL3/SDL_video.h>
#include <cstdint>

struct Framebuffer {
    int width;
    int height;
    int pitch;        // distance in bytes between rows of pixels
    uint32_t* pixels;

    Framebuffer();
    ~Framebuffer();
};

struct Color {
    uint8_t r, g, b;
};

void draw_pixel(Framebuffer& fb, int x, int y, Color cl);
void clear_screeen(Framebuffer& fb, Color cl);
