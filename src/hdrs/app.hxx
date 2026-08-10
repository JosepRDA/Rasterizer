#pragma once

#include "framebuffer.hxx"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <memory>

class Application
{
public:
    using AppPtr = std::unique_ptr<Application>;
    static AppPtr create(int winWidth, int winHeight);

    bool init();
    void mainLoop();

    ~Application();
private:
    Application(int winWidth, int winHeight);

    int winWidth, winHeight;
    Framebuffer fb;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

