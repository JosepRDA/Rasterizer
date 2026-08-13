#include "hdrs/framebuffer.hxx"
#include <cstdint>
#include <cstring>
#include <cmath>

Framebuffer::Framebuffer(int winWidth, int winHeight)
    : width{winWidth}, height{winHeight}
{
    pitch = winWidth * sizeof(uint32_t);
    pixels = new uint32_t[pitch * height]; // allocating stuff   
}

Framebuffer::~Framebuffer()
{
    delete[] pixels;
}

// TODO: finish this helper function
static uint32_t convertColorHex(Color cl)
{
    // perform math to convert the elements of the color into a hex code ***
    // probably something to do with interpolation betwee r, g and b
    // and then calling the hex function from c's standard library
    return 0;
}

void Framebuffer::drawPixel(int x, int y, Color cl)
{
    uint32_t col = convertColorHex(cl);
    pixels[y * width + x] = col; // RED, 255
}

void Framebuffer::clearScreen(Color cl)
{
    uint32_t colorPix = convertColorHex(cl);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixels[y * width + x] = colorPix; // RED, 255
        }
    }
}

// for when you know the color's hex directly
void Framebuffer::clearScreen(uint32_t cl)
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixels[y * width + x] = cl; // RED, 255
        }
    }
}

void Framebuffer::write(void* texture_pixels, int texture_pitch)
{
    for (int y = 0; y < height; ++y) {
        std::memcpy(
            static_cast<uint8_t*>(texture_pixels) + y * texture_pitch,
            reinterpret_cast<uint8_t*>(pixels) + y * pitch,
            width * sizeof(uint32_t)
        );
    }
}

