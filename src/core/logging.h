#pragma once

#include <format>

namespace logging {
    enum LogLevel {
        Error = 0,
        Info = 1,
        Debug = 2
    };

    class Logger {
    public:
        virtual void write(const std::string &str) = 0;
    };

    extern std::vector<std::shared_ptr<Logger>> loggers;

    extern void setLogLevel(LogLevel level);
    extern void write(LogLevel level, const std::string& message);

    template<typename... Args>
    inline void error(const std::format_string<Args...> &fmt, Args... args) {
        write(LogLevel::Error, std::format(fmt, args...));
    }

    template<typename... Args>
    inline void info(const std::format_string<Args...> &fmt, Args... args) {
        write(LogLevel::Info, std::format(fmt, args...));
    }

    template<typename... Args>
    inline void debug(const std::format_string<Args...> &fmt, Args... args) {
        write(LogLevel::Debug, std::format(fmt, args...));
    }
}
