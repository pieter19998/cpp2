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
    void Log(const std::string& data);
    void PrintAndLog(const std::string& message);
    void ClearFile();
};
