#include "hdrs/framebuffer.hxx"

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

void draw_pixel(Framebuffer& fb, int x, int y, Color cl)
{
}

void clear_screeen(Framebuffer& fb, Color cl)
{
}
