#ifndef WINDOW_SDL_H
#define WINDOW_SDL_H

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <GL/glew.h>
#include <string>
#include <memory>

#include "window.h"

extern const float SCREEN_WIDTH;
extern const float SCREEN_HEIGHT;

// Manage game's window and drawing in this window.
// The window title bar gives some info, as game's title
// or FPS counter.
class WindowSdl : public IWindow
{
public:
    WindowSdl(const std::string &title);
    virtual ~WindowSdl();

    bool init(int xPos, int yPos, int width, int height, bool isFullscreen) override;
    //bool should_close();
    //void handle_close();
    void updateFpsCounter(long dt) override;
    void clear() override;
    void swapBuffer() override;
    void clean() override;

private:
    SDL_Window *window;
    SDL_GLContext context;
    const std::string &title;

    double previousSeconds;
    double currentSeconds;
    int frameCount;

    WindowSdl();
    WindowSdl(const WindowSdl &);
    WindowSdl &operator=(const WindowSdl &);
};

#endif