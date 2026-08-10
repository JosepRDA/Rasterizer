#include "hdrs/app.hxx"
#include "hdrs/framebuffer.hxx"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <cstdint>
#include <cstring>
#include <memory>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;

Application::AppPtr Application::create(int winWidth, int winHeight)
{
    return std::unique_ptr<Application>(new Application(winWidth, winHeight));
}

Application::Application(int winWidth, int winHeight)
    : winWidth{winWidth}, winHeight{winHeight}
{
    SDL_SetAppMetadata("Software Renderer in SDL3", "0.1", "com.renderer");

    fb.width = winWidth;
    fb.height = winHeight;
    fb.pitch = winWidth * sizeof(uint32_t);
    fb.pixels = new uint32_t[fb.pitch * fb.height]; // allocating stuff   
}

bool Application::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if(!SDL_CreateWindowAndRenderer("Software renderer", WIDTH, HEIGHT,
                    SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    } 
    SDL_SetRenderLogicalPresentation(renderer,WIDTH, HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
   
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    if (!texture) {
        SDL_Log("Couldn't create streaming texture: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Application::mainLoop()
{
    bool done = false;
    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        // updating the framebuffer 
        for (int y = 0; y < fb.height; y++) {
            for (int x = 0; x < fb.width; x++) {
                fb.pixels[y * fb.width + x] = 0xFF0000FF; // RED, 255
            }
        }
       
        void* texture_pixels;
        int texture_pitch;
        if (SDL_LockTexture(texture, NULL, &texture_pixels, &texture_pitch)) {
            for (int y = 0; y < fb.height; ++y) {
                std::memcpy(
                        static_cast<uint8_t*>(texture_pixels) + y * texture_pitch,
                        reinterpret_cast<uint8_t*>(fb.pixels) + y * fb.pitch,
                        fb.width * sizeof(uint32_t)
                );
            }
            
            SDL_UnlockTexture(texture);
        }

        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        SDL_FRect dst_rect = {
            0.0f,
            0.0f,
            (float)window_width,
            (float)window_height
        };
        SDL_RenderTexture(renderer, texture, NULL, &dst_rect);

        SDL_RenderPresent(renderer);  /* put it all on the screen! */
    }
}

Application::~Application()
{    
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    delete[] fb.pixels;
    SDL_Quit();
}

int main (void) {
    auto app = Application::create(WIDTH, HEIGHT);
    if (app->init()) {
        app->mainLoop();
    } else {
        // std::println(stderr, "Error or smth");
        return 1;
    }
    return 0;
}
