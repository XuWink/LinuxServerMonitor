#include "Logger.hpp"

int main() {
    Logger& logger = Logger::getInstance();
    logger.setLogLevel(Logger::LogLevel::DEBUG);

    logger.debug("This is a debug message");
    logger.info("This is an info message");
    logger.warning("This is a warning message");
    logger.error("This is an error message");

    return 0;
}