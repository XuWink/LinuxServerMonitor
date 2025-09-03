#include "Logger.hpp"

#include <ctime>
#include <stdexcept>

// -------------------------- 静态成员变量定义（与头文件声明完全一致） --------------------------
std::unique_ptr<Logger, Logger::Deleter> Logger::instance_ = nullptr;
std::mutex                               Logger::mutex_;

// -------------------------- 私有构造函数实现（原逻辑保留） --------------------------
Logger::Logger() : current_level_(LogLevel::INFO) {
    log_file_.open("app.log", std::ios::app);
    if (!log_file_.is_open()) {
        throw std::runtime_error("Failed to open log file: app.log");
    }
}

// -------------------------- 私有析构函数实现（原逻辑保留） --------------------------
Logger::~Logger() {
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

// -------------------------- 单例获取方法（线程安全） --------------------------
Logger & Logger::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!instance_) {
        // 关键：使用自定义删除器构造 unique_ptr
        instance_ = std::unique_ptr<Logger, Logger::Deleter>(new Logger());
    }
    return *instance_;
}

// -------------------------- 日志级别设置（原逻辑保留） --------------------------
void Logger::setLogLevel(LogLevel level) {
    current_level_ = level;
}

// -------------------------- 时间戳获取（原逻辑保留） --------------------------
std::string Logger::getCurrentTime() const {
    std::time_t now = std::time(nullptr);
    char        buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

// -------------------------- 日志格式化（原逻辑保留） --------------------------
std::string Logger::formatMessage(LogLevel level, const std::string & message) const {
    std::stringstream ss;
    ss << "[" << getCurrentTime() << "] ";
    switch (level) {
        case LogLevel::DEBUG:
            ss << "[DEBUG]   ";
            break;
        case LogLevel::INFO:
            ss << "[INFO]    ";
            break;
        case LogLevel::WARNING:
            ss << "[WARNING] ";
            break;
        case LogLevel::ERROR:
            ss << "[ERROR]   ";
            break;
    }
    ss << message << std::endl;
    return ss.str();
}

// -------------------------- 原无占位符日志方法实现（保留） --------------------------
void Logger::debug(const std::string & message) {
    if (static_cast<int>(LogLevel::DEBUG) >= static_cast<int>(current_level_)) {
        std::string                 formatted_msg = formatMessage(LogLevel::DEBUG, message);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

void Logger::info(const std::string & message) {
    if (static_cast<int>(LogLevel::INFO) >= static_cast<int>(current_level_)) {
        std::string                 formatted_msg = formatMessage(LogLevel::INFO, message);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

void Logger::warning(const std::string & message) {
    if (static_cast<int>(LogLevel::WARNING) >= static_cast<int>(current_level_)) {
        std::string                 formatted_msg = formatMessage(LogLevel::WARNING, message);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

void Logger::error(const std::string & message) {
    if (static_cast<int>(LogLevel::ERROR) >= static_cast<int>(current_level_)) {
        std::string                 formatted_msg = formatMessage(LogLevel::ERROR, message);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}
