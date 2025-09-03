#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>  // 用于 std::index_sequence

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

class Logger {
  public:
    // 禁止拷贝构造和赋值（单例核心）
    Logger(const Logger &)             = delete;
    Logger & operator=(const Logger &) = delete;

    // 单例获取接口
    static Logger & getInstance();
    // 日志级别控制
    void            setLogLevel(LogLevel level);

    // -------------------------- 原无占位符日志方法（保留） --------------------------
    void debug(const std::string & message);
    void info(const std::string & message);
    void warning(const std::string & message);
    void error(const std::string & message);

    // -------------------------- 新增带占位符日志方法（模板） --------------------------
    template <typename... Args> void debug(const std::string & format, Args &&... args);
    template <typename... Args> void info(const std::string & format, Args &&... args);
    template <typename... Args> void warning(const std::string & format, Args &&... args);
    template <typename... Args> void error(const std::string & format, Args &&... args);

    // -------------------------- 自定义删除器（核心：解决析构权限） --------------------------
    struct Deleter {
        void operator()(Logger * ptr) const {
            if (ptr != nullptr) {
                ptr->~Logger();          // 调用私有析构（Deleter 是 Logger 内部类，有权限）
                ::operator delete(ptr);  // 释放内存
            }
        }
    };

  private:
    // 单例私有构造/析构（析构无需 friend 授权，Deleter 已能访问）
    Logger();
    ~Logger();

    // -------------------------- 原辅助方法（保留） --------------------------
    // 格式化日志（时间戳 + 级别）
    std::string formatMessage(LogLevel level, const std::string & message) const;
    // 获取当前时间字符串（YYYY-MM-DD HH:MM:SS）
    std::string getCurrentTime() const;

    // -------------------------- 修正：占位符替换逻辑（编译期展开） --------------------------
    // 子函数：单个参数替换（编译期索引）
    template <size_t Idx, typename Tuple>
    void appendSingleArg(std::stringstream & ss, const Tuple & args, size_t & arg_used) const {
        if (arg_used < std::tuple_size<Tuple>::value) {
            ss << std::get<Idx>(args);  // Idx 是编译期常量，符合 std::get 要求
            arg_used++;
        }
    }

    // 子函数：展开所有参数并替换占位符
    template <typename Tuple, size_t... Idxs>
    void expandArgsAndReplace(std::stringstream & ss,
                              const std::string & format,
                              const Tuple &       args,
                              std::index_sequence<Idxs...>) const {
        size_t       pos       = 0;
        size_t       arg_used  = 0;
        const size_t arg_count = std::tuple_size<Tuple>::value;

        while (pos < format.size()) {
            size_t placeholder_pos = format.find("{}", pos);
            if (placeholder_pos == std::string::npos) {
                ss << format.substr(pos);
                break;
            }

            // 追加占位符前内容
            ss << format.substr(pos, placeholder_pos - pos);
            // 替换占位符（参数足够则替换，否则保留）
            if (arg_used < arg_count) {
                (appendSingleArg<Idxs>(ss, args, arg_used), ...);  // C++17 折叠表达式
            } else {
                ss << "{}";
            }

            pos = placeholder_pos + 2;  // 跳过 "{}"
        }
    }

    // 对外接口：格式化带占位符的消息
    template <typename... Args> std::string formatWithPlaceholders(const std::string & format, Args &&... args) const {
        std::stringstream ss;
        auto              args_tuple = std::make_tuple(std::forward<Args>(args)...);
        auto              idx_seq    = std::make_index_sequence<sizeof...(Args)>();
        expandArgsAndReplace(ss, format, args_tuple, idx_seq);
        return ss.str();
    }

    // -------------------------- 成员变量（声明与定义需一致） --------------------------
    static std::unique_ptr<Logger, Deleter> instance_;       // 带自定义删除器的声明
    static std::mutex                       mutex_;          // 线程安全锁
    std::ofstream                           log_file_;       // 日志文件流
    LogLevel                                current_level_;  // 当前日志级别
};

// -------------------------- 模板方法实现（头文件中，避免链接错误） --------------------------
template <typename... Args> void Logger::debug(const std::string & format, Args &&... args) {
    if (static_cast<int>(LogLevel::DEBUG) >= static_cast<int>(current_level_)) {
        std::string                 content       = formatWithPlaceholders(format, std::forward<Args>(args)...);
        std::string                 formatted_msg = formatMessage(LogLevel::DEBUG, content);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

template <typename... Args> void Logger::info(const std::string & format, Args &&... args) {
    if (static_cast<int>(LogLevel::INFO) >= static_cast<int>(current_level_)) {
        std::string                 content       = formatWithPlaceholders(format, std::forward<Args>(args)...);
        std::string                 formatted_msg = formatMessage(LogLevel::INFO, content);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

template <typename... Args> void Logger::warning(const std::string & format, Args &&... args) {
    if (static_cast<int>(LogLevel::WARNING) >= static_cast<int>(current_level_)) {
        std::string                 content       = formatWithPlaceholders(format, std::forward<Args>(args)...);
        std::string                 formatted_msg = formatMessage(LogLevel::WARNING, content);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

template <typename... Args> void Logger::error(const std::string & format, Args &&... args) {
    if (static_cast<int>(LogLevel::ERROR) >= static_cast<int>(current_level_)) {
        std::string                 content       = formatWithPlaceholders(format, std::forward<Args>(args)...);
        std::string                 formatted_msg = formatMessage(LogLevel::ERROR, content);
        std::lock_guard<std::mutex> lock(mutex_);
        log_file_ << formatted_msg;
        std::cout << formatted_msg;
    }
}

#endif  // LOGGER_HPP
