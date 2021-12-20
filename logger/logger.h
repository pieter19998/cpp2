#pragma once
#include <memory>
#include <string>
#include "logging.h"
class Logger {
private:
    Logger() = default;
    static Logger _singleton;
public:
    Logger(Logger &other) = delete;
    void operator=(const Logger &) = delete;
    static Logger& get();
    void log(const std::string& data);
};
