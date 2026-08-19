#include "hdrs/app.hxx"
#include "hdrs/framebuffer.hxx"
#include <SDL3/SDL_video.h>
#include <cstring>

Application::AppPtr Application::create(int winWidth, int winHeight)
{
    return Application::AppPtr(new Application(winWidth, winHeight));
}

Application::Application(int winWidth, int winHeight)
    : winWidth{winWidth}, winHeight{winHeight}, fb(winWidth, winHeight)
{
    SDL_SetAppMetadata("Software Renderer in SDL3", "0.1", "renderer");
}

bool Application::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if(!SDL_CreateWindowAndRenderer("Software renderer", winWidth, winHeight,
                    SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    } 
    SDL_SetRenderLogicalPresentation(renderer, winWidth, winHeight, SDL_LOGICAL_PRESENTATION_DISABLED);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, winWidth, winHeight);
    if (!texture) {
        SDL_Log("Couldn't create streaming texture: %s", SDL_GetError());
        return false;
    }

    return true;
}

// not my proudest coding
void Application::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            done = true;
        }
    }
}

void Application::mainLoop()
{
    while (!done) 
    {
        handleEvents();           

        // has to be called at the start of the frame because the last draw command
        // takes priority (overwrites the previous one, if both write to the same pixel)
        // much like in opengl
        fb.clearScreen(RED);

        // perform math for triangle collision here
        // right now drawing a cyan rectangle in the middle of the screen
        for (int y = 150; y < fb.height - 200; y++) {
            for (int x = 100; x < fb.width - 300; x++) {
                fb.pixels[y * fb.width + x] = CYAN; // RED, 255
            }
        }

        void* texture_pixels;
        int texture_pitch;
        if (SDL_LockTexture(texture, NULL, &texture_pixels, &texture_pitch)) {
            fb.write(texture_pixels, texture_pitch);
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}

int main(void) 
{
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;

    auto app = Application::create(WIDTH, HEIGHT);
    if (!app->init()) {
        return 1;
    }
    app->mainLoop();

    return 0;
}
