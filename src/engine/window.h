#ifndef WINDOW_H
#define WINDOW_H

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#endif

#include <GL/glew.h>

extern const float SCREEN_WIDTH;
extern const float SCREEN_HEIGHT;


// Manage game's window and drawing in this window.
// The window title bar gives some info, as game's title
// or FPS counter.
class Window
{
public:
    Window();
    virtual ~Window();

    bool init(const char *windowTitle, int xPos, int yPos, int width, int height, bool isFullscreen);
    //bool should_close();
    //void handle_close();
    void updateFpsCounter(long dt);
    void clear();
    void swapBuffer();
    void clean();

private:
    SDL_Window *window;
	SDL_GLContext context;
    const char *title;

    double previousSeconds;
    double currentSeconds;
    int frameCount;

    Window(const Window &);
    Window &operator=(const Window &);
};

#endif