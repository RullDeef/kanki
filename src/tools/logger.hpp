#pragma once

#include <string>
#include <iostream>

#define LOG_METHOD(...) Logger::info(std::string(typeid(*this).name()) + "::" + __func__ + ": " + std::string(__VA_ARGS__))
#define WARN_METHOD(...) Logger::warn(std::string(typeid(*this).name()) + "::" + __func__ + ": " + std::string(__VA_ARGS__))
#define ERROR_METHOD(...) Logger::error(std::string(typeid(*this).name()) + "::" + __func__ + ": " + std::string(__VA_ARGS__))

class Logger
{
public:
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

private:
    enum class LogLevel { INFO, WARN, ERROR };

    static void log(LogLevel level, const std::string& message);
};
