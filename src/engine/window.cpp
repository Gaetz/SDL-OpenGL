
#include "window.h"

Window::Window() : previousSeconds(0),
                   currentSeconds(0),
                   frameCount(0)
{
}

Window::~Window()
{
}

bool Window::init(const char *windowTitle, int xPos, int yPos, int width, int height, bool isFullscreen)
{
    int flags = SDL_WINDOW_OPENGL;
    if (isFullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Subsystems initialised");

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // Window
        title = windowTitle;
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
        if (window)
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Window initialised");
        }
        else
            return false;

        // OpenGL context
        context = SDL_GL_CreateContext(window);
        if (context)
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Context initialised");
        }
        else
            return false;

        // OpenGL setup
        glewExperimental = GL_TRUE;
        GLenum initGLEW(glewInit());
        if (initGLEW == GLEW_OK)
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "GLEW initialised");
        }
        else
            return false;

        glViewport(0, 0, width, height);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return true;
    }
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL initialisation failed");
        return false;
    }
}

void Window::updateFpsCounter(long dt)
{
    double elapsedSeconds;

    currentSeconds += dt / 1000.0;
    elapsedSeconds = currentSeconds - previousSeconds;
    /* limit text updates to 4 per second */
    if (elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        char tmp[128];
        double fps = (double)frameCount / elapsedSeconds;
        sprintf(tmp, "%s @ fps: %.2f", title, fps);
        SDL_SetWindowTitle(window, tmp);
        frameCount = 0;
    }
    frameCount++;
}

void Window::clear()
{
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffer()
{
    SDL_GL_SwapWindow(window);
}

void Window::clean()
{
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bye :)");
}