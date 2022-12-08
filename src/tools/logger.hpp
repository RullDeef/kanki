#pragma once

#include <string>
#include <iostream>

#define LOG_FUNC(...) Logger::info(std::string(__func__) + ": " + std::string(__VA_ARGS__))
#define WARN_FUNC(...) Logger::warn(std::string(__func__) + ": " + std::string(__VA_ARGS__))
#define ERROR_FUNC(...) Logger::error(std::string(__func__) + ": " + std::string(__VA_ARGS__))

#define LOG_METHOD(...) Logger::info(std::string(typeid(*this).name()) + "::" + __func__ + ": " + std::string(__VA_ARGS__))
#define WARN_METHOD(...) Logger::warn(std::string(typeid(*this).name()) + "::" + __func__ + ": " + std::string(__VA_ARGS__))
#define ERROR_METHOD(...) Logger::error(std::string(typeid(*this).name()) + "::" + __func__ + ": " + std::string(__VA_ARGS__))

#define TRY_FUNC(func)              \
    try                             \
    {                               \
        func;                       \
    }                               \
    catch (const std::exception &e) \
    {                               \
        ERROR_FUNC(e.what());       \
    }

#define TRY_METHOD(mtd)             \
    try                             \
    {                               \
        mtd;                        \
    }                               \
    catch (const std::exception &e) \
    {                               \
        ERROR_METHOD(e.what());     \
    }

class Logger
{
public:
    static void info(const std::string &message);
    static void warn(const std::string &message);
    static void error(const std::string &message);

    static void enable();
    static void disable();

private:
    enum class LogLevel
    {
        INFO,
        WARN,
        ERROR
    };
    static bool enabled;

    static void log(LogLevel level, const std::string &message);
};
