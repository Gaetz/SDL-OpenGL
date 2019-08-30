#ifndef WINDOW_SDL_H
#define WINDOW_SDL_H

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <GL/glew.h>

#include "window.h"

extern const float SCREEN_WIDTH;
extern const float SCREEN_HEIGHT;
extern LogConfig LOG_CONFIG;

// Used by SDL_Window unique pointer
struct SdlWindowDestroyer
{
    void operator()(SDL_Window *window) const
    {
        SDL_DestroyWindow(window);
    }
};

// Manage game's window and drawing in this window.
// The window title bar gives some info, as game's title
// or FPS counter.
class WindowSdl : public IWindow
{
public:
    WindowSdl(const std::string &title);
    virtual ~WindowSdl();

    bool init(int xPos, int yPos, int width, int height, bool isFullscreen) override;
    void logGlParams() override;
    //bool should_close();
    //void handle_close();
    void updateFpsCounter(long dt) override;
    void clear() override;
    void swapBuffer() override;
    void clean() override;

private:
    std::unique_ptr<SDL_Window, SdlWindowDestroyer> window;
    SDL_GLContext context;
    const std::string &title;

    double previousSeconds;
    double currentSeconds;
    int frameCount;

    /*
    void debugGlErrorCallback(  GLenum        source,
                                GLenum        type,
                                GLuint        id,
                                GLenum        severity,
                                GLsizei       length,
                                const GLchar* message,
                                GLvoid*       userParam);

    const char* debugGlSeverityToStr(GLenum severity);
    const char* debugGlTypeToStr(GLenum type);
    const char* debugGlSourceToStr(GLenum source);
    */


    WindowSdl();
    WindowSdl(const WindowSdl &);
    WindowSdl &operator=(const WindowSdl &);
};

#endif