#include <ctime>
#include "logger.hpp"

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

bool Logger::enabled = false;

void Logger::info(const std::string &message)
{
    log(LogLevel::INFO, message);
}

void Logger::warn(const std::string &message)
{
    log(LogLevel::WARN, message);
}

void Logger::error(const std::string &message)
{
    log(LogLevel::ERROR, message);
}

void Logger::enable()
{
    enabled = true;
}

void Logger::disable()
{
    enabled = false;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
static char *currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct = *localtime(&now);

    static char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %T", &tstruct);

    return buf;
}

void Logger::log(LogLevel level, const std::string &message)
{
    if (!enabled)
        return;

    switch (level)
    {
    case LogLevel::INFO:
        std::cerr << CYAN;
        break;
    case LogLevel::WARN:
        std::cerr << YELLOW;
        break;
    case LogLevel::ERROR:
        std::cerr << BOLDRED;
        break;
    }

    std::cerr << "[" << currentDateTime() << "]: " << message << RESET << std::endl;
}
