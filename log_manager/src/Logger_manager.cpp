#include "logger_manager.h"

// 初始化静态成员变量
std::unique_ptr<Logger> Logger::instance_ = nullptr;
std::mutex Logger::mutex_;

// 私有构造函数
Logger::Logger() : current_level_(LogLevel::INFO) {
    log_file_.open("app.log", std::ios::app);
    if (!log_file_.is_open()) {
        throw std::runtime_error("Failed to open log file");
    }
}

Logger::~Logger() {
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

// 获取单例实例（线程安全）
Logger& Logger::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!instance_) {
        instance_ = std::unique_ptr<Logger>(new Logger());
    }
    // *instance_ 解引用 std::unique_ptr，返回它指向的 Logger 对象的引用
    return *instance_;
}

// 设置日志级别
void Logger::setLogLevel(LogLevel level) {
    current_level_ = level;
}

// 获取当前时间字符串
std::string Logger::getCurrentTime() const {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

// 格式化日志消息
std::string Logger::formatMessage(LogLevel level, const std::string& message) const {
    std::stringstream ss;
    ss << "[" << getCurrentTime() << "] ";
    switch (level) {
        case LogLevel::DEBUG: ss << "[DEBUG] "; break;
        case LogLevel::INFO: ss << "[INFO] "; break;
        case LogLevel::WARNING: ss << "[WARNING] "; break;
        case LogLevel::ERROR: ss << "[ERROR] "; break;
    }
    ss << message << std::endl;
    return ss.str();
}

// 快捷日志方法
void Logger::debug(const std::string& message) {
    if (static_cast<int>(LogLevel::DEBUG) >= static_cast<int>(current_level_)) {
        std::string formatted_msg = formatMessage(LogLevel::DEBUG, message);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg; // 可选：同时输出到控制台
    }
}

void Logger::info(const std::string& message) {
    if (static_cast<int>(LogLevel::INFO) >= static_cast<int>(current_level_)) {
        std::string formatted_msg = formatMessage(LogLevel::INFO, message);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

void Logger::warning(const std::string& message) {
    if (static_cast<int>(LogLevel::WARNING) >= static_cast<int>(current_level_)) {
        std::string formatted_msg = formatMessage(LogLevel::WARNING, message);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

void Logger::error(const std::string& message) {
    if (static_cast<int>(LogLevel::ERROR) >= static_cast<int>(current_level_)) {
        std::string formatted_msg = formatMessage(LogLevel::ERROR, message);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}