#include "logger.h"

Logger Logger::_singleton;

void Logger::log(const std::string &data) {
    WriteToLogFile<std::string>("log.txt",data);
}

Logger &Logger::get() {
    return _singleton;
}