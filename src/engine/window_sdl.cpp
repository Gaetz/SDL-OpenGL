#include "window_sdl.h"



WindowSdl::WindowSdl(const std::string &title) : title(title),
                                           previousSeconds(0),
                                           currentSeconds(0),
                                           frameCount(0)
{
}

WindowSdl::~WindowSdl()
{
    SDL_Quit();
    LOG(Info) << "Bye :)";
}


// Breakpoints that should ALWAYS trigger (EVEN IN RELEASE BUILDS) [x86]!
#ifdef _MSC_VER
# define eTB_CriticalBreakPoint() if (IsDebuggerPresent ()) __debugbreak ();
#else
# define eTB_CriticalBreakPoint() asm (" int $3");
#endif

const char* ETB_GL_DEBUG_SOURCE_STR (GLenum source)
{
  static const char* sources [] = {
    "API",   "Window System", "Shader Compiler", "Third Party", "Application",
    "Other", "Unknown"
  };

  int str_idx =
    std::min ( (unsigned long) ( source - GL_DEBUG_SOURCE_API),
            sizeof (sources) / sizeof (const char *) );

  return sources [str_idx];
}

const char* ETB_GL_DEBUG_TYPE_STR (GLenum type)
{
  static const char* types [] = {
    "Error",       "Deprecated Behavior", "Undefined Behavior", "Portability",
    "Performance", "Other",               "Unknown"
  };

  int str_idx =
    std::min ( (unsigned long) ( type - GL_DEBUG_TYPE_ERROR),
            sizeof (types) / sizeof (const char *) );

  return types [str_idx];
}

const char* ETB_GL_DEBUG_SEVERITY_STR (GLenum severity)
{
  static const char* severities [] = {
    "High", "Medium", "Low", "Unknown"
  };

  int str_idx =
    std::min ( (unsigned long)(severity - GL_DEBUG_SEVERITY_HIGH),
            sizeof (severities) / sizeof (const char *) );

  return severities [str_idx];
}

unsigned int ETB_GL_DEBUG_SEVERITY_COLOR (GLenum severity)
{
  static unsigned int severities [] = {
    0xff0000ff, // High (Red)
    0xff00ffff, // Med  (Yellow)
    0xff00ff00, // Low  (Green)
    0xffffffff  // ???  (White)
  };

  int col_idx =
    std::min ( (unsigned long)(severity - GL_DEBUG_SEVERITY_HIGH),
            sizeof (severities) / sizeof (unsigned int) );

  return severities [col_idx];
}

#include <iostream>
using std::cout;
using std::endl;

void ETB_GL_ERROR_CALLBACK (GLenum        source,
                            GLenum        type,
                            GLuint        id,
                            GLenum        severity,
                            GLsizei       length,
                            const GLchar* message,
                            GLvoid*       userParam)
{
    cout << " --- OpenGL ERROR -------------------" << endl;
    cout << "message: "<< message << endl;
    cout << "source: "<< ETB_GL_DEBUG_SOURCE_STR(source) << endl;
    cout << "type: " << ETB_GL_DEBUG_TYPE_STR(type) << endl;
 
    cout << "id: " << id << endl;
    cout << "severity: " << ETB_GL_DEBUG_SEVERITY_STR(severity);
    cout << endl;
    cout << " ---------------------------" << endl;
}


bool WindowSdl::init(int xPos, int yPos, int width, int height, bool isFullscreen)
{
    int flags = SDL_WINDOW_OPENGL;
    if (isFullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        LOG(Info) << "Subsystems initialised";

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        
        // WindowSdl
        window = std::unique_ptr<SDL_Window, SdlWindowDestroyer>(
            SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, flags)
        );
        if (window)
        {
            LOG(Info) << "WindowSdl initialised";
        }
        else
            return false;

        // OpenGL context
        context = SDL_GL_CreateContext(window.get());
        if (context)
        {
            LOG(Info) << "OpenGL Context initialised";
        }
        else
            return false;

        // OpenGL setup
        glewExperimental = GL_TRUE;
        GLenum initGLEW(glewInit());
        if (initGLEW == GLEW_OK)
        {
            LOG(Info) << "GLEW initialised";
        }
        else
            return false;

        glViewport(0, 0, width, height);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        if (glDebugMessageControlARB != NULL) {
            glEnable                  (GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback ((GLDEBUGPROCARB)ETB_GL_ERROR_CALLBACK, NULL);
            GLuint unusedIds = 0;
            glDebugMessageControl  (GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, GL_TRUE);
        }

        return true;
    }
    else
    {
        LOG(Error) << "SDL initialisation failed";
        return false;
    }
}

void WindowSdl::logGlParams()
{
    GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };
    const char *names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };
    LOG(Info) << "-----------------------------";
    LOG(Info) << "GL Context Params:";
    // integers - only works if the order is 0-10 integer return types
    for (int i = 0; i < 10; i++)
    {
        int v = 0;
        glGetIntegerv(params[i], &v);
        LOG(Info) << names[i] << " " << v;
    }
    // others
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    LOG(Info) << names[10] << " " << v[0] << " " << v[1];
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    LOG(Info) << names[11] << " " << (unsigned int)s;
    LOG(Info) << "";
};

void WindowSdl::updateFpsCounter(long dt)
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
        sprintf(tmp, "%s @ fps: %.2f", title.c_str(), fps);
        SDL_SetWindowTitle(window.get(), tmp);
        frameCount = 0;
    }
    frameCount++;
}

void WindowSdl::clear()
{
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void WindowSdl::swapBuffer()
{
    // check OpenGL error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        LOG(Error) << "OpenGL error: " << err;
    }

    SDL_GL_SwapWindow(window.get());
}

void WindowSdl::clean()
{
    // SDL_DestroyWindow(window); Handled by unique_ptr
    SDL_GL_DeleteContext(context);
}

std::unique_ptr<IWindow> IWindow::create(const std::string& title)
{
    return std::make_unique<WindowSdl>(title);
}