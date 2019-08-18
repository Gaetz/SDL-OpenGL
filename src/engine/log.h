// Inspired from http://www.drdobbs.com/cpp/logging-in-c/201804215
// and https://github.com/zuhd-org/easyloggingpp

#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

#define GL_LOG_FILE "gl.log"

enum LogLevel
{
    Error,
    Warning,
    Info,
    Debug
};

struct LogConfig
{
    LogLevel reporting_level = Info;
    bool restart = false;
};

extern LogConfig LOG_CONFIG;

// General purpose logging class
// Logs in standard output and in a file, configured
// with the GL_LOG_FILE macro.
// Usage : LOG(MessageLevel) << "Message"
class Log
{
public:
    Log();
    virtual ~Log();
    std::ostringstream &get(LogLevel level = Info);
    static void restart();

private:
    std::ostringstream os;
    static std::ofstream file;

    std::string getLabel(LogLevel type);

    Log(const Log &);
    Log &operator=(const Log &);
};

#define LOG(level)                          \
    if (level > LOG_CONFIG.reporting_level) \
        ;                                   \
    else                                    \
        Log().get(level)

#endif