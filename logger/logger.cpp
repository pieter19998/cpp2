#include "logger.h"

Logger Logger::_singleton;

void Logger::Log(const std::string &data) {
    WriteToLogFile<std::string>("log.txt",data);
}

Logger &Logger::get() {
    return _singleton;
}

void Logger::PrintAndLog(const std::string &message) {
    Log(message);
    std::cout << message << std::endl;
}

void Logger::ClearFile() {
    std::remove("log.txt");
}