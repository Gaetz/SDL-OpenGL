#include <GL/glew.h>
#include <algorithm>
#include "log.h"

// Breakpoints that should ALWAYS trigger (EVEN IN RELEASE BUILDS) [x86]!
#ifdef _MSC_VER
#define eTB_CriticalBreakPoint() \
    if (IsDebuggerPresent())     \
        __debugbreak();
#else
#define eTB_CriticalBreakPoint() asm(" int $3");
#endif

const char *debugGlSourceToStr(GLenum source)
{
    static const char *sources[] = {
        "API", "Window System", "Shader Compiler", "Third Party", "Application",
        "Other", "Unknown"};

    int str_idx =
        std::min(source - GL_DEBUG_SOURCE_API, (GLuint)((long)sizeof(sources) / (long)sizeof(const char *)));

    return sources[str_idx];
}

const char *debugGlTypeToStr(GLenum type)
{
    static const char *types[] = {
        "Error", "Deprecated Behavior", "Undefined Behavior", "Portability",
        "Performance", "Other", "Unknown"};

    int str_idx = std::min(type - GL_DEBUG_TYPE_ERROR, (GLuint)((long)sizeof(types) / (long)sizeof(const char *)));

    return types[str_idx];
}

const char *debugGlSeverityToStr(GLenum severity)
{
    /*static const char* severities [] = {
    "High", "Medium", "Low", "Unknown"
  };

  int str_idx =
    std::min (severity - GL_DEBUG_SEVERITY_HIGH, (GLuint)((long)sizeof (severities) / (long)sizeof (const char *)) );

  return severities [str_idx];*/
    return "unknown";
}

void debugGlErrorCallback(GLenum source,
                          GLenum type,
                          GLuint id,
                          GLenum severity,
                          GLsizei length,
                          const GLchar *message,
                          GLvoid *userParam)
{
    LOG(Error) << " --- OpenGL ERROR -------------------"
    << "\n" << "message: " << message
    << "\n" << "source: " << debugGlSourceToStr(source)
    << "\n" << "type: " << debugGlTypeToStr(type)
    << "\n" << "id: " << id
    << "\n" << "severity: " << debugGlSeverityToStr(severity);
}
