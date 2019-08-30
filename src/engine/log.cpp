#include "log.h"
#include <ctime>
#include <iostream>

Log::Log()
{
    file.open(GL_LOG_FILE, std::fstream::app);
}

Log::~Log()
{
    os << std::endl;
    file << os.str();
    std::cout << os.str();
    os.clear();
    file.close();
}

std::ofstream Log::file;

void Log::restart()
{
    file.open(GL_LOG_FILE, std::fstream::trunc);
    file.close();
}

std::ostringstream &Log::get(LogLevel level)
{
    if (!file)
        return os;

    // Log
    time_t now;
    struct tm *timeinfo;
    char date[19];

    time(&now);
    timeinfo = localtime(&now);
    strftime(date, 19, "%y-%m-%d %H:%M:%S", timeinfo);

    // Log
    os << date << " " << getLabel(level) << ": \t";
    return os;
}

std::string Log::getLabel(LogLevel type)
{
    std::string label;
    switch (type)
    {
    case Debug:
        label = "DEBUG";
        break;
    case Info:
        label = "INFO ";
        break;
    case Warning:
        label = "WARN ";
        break;
    case Error:
        label = "ERROR";
        break;
    }
    return label;
}