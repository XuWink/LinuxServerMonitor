#ifndef LOGGER_MANAGER_H_
#define LOGGER_MANAGER_H_

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>

// #include "block_queue.hpp"

// TODO 添加阻塞队列

class Logger {
  public:
    // 禁止拷贝和赋值
    Logger(const Logger &)             = delete;
    Logger & operator=(const Logger &) = delete;

    // 获取单例实例（线程安全）
    static Logger & getInstance();

    // 设置日志级别
    enum class LogLevel { DEBUG, INFO, WARNING, ERROR };
    void setLogLevel(LogLevel level);

    // 快捷日志方法
    void debug(const std::string & message);
    void info(const std::string & message);
    void warning(const std::string & message);
    void error(const std::string & message);

    ~Logger();

  private:
    // 私有构造函数和析构函数
    Logger();

    // 日志级别和文件流
    LogLevel      current_level_;
    std::ofstream log_file_;

    // 静态成员变量和互斥锁
    static std::unique_ptr<Logger> instance_;
    static std::mutex              mutex_;

    // 辅助方法
    std::string getCurrentTime() const;
    std::string formatMessage(LogLevel level, const std::string & message) const;
};

#endif
