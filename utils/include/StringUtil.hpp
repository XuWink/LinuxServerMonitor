#ifndef STRING_UTIL_
#define STRING_UTIL_

#include "Logger.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace util {

class StringUtil {
  private:
    /* data */
  public:
    StringUtil();
    ~StringUtil();

    /// @brief 去除字符串首尾的空格和制表符
    /// @param s 待修剪的字符串（引用传递，直接修改原字符串）
    static void TrimString(std::string & s);

    /// @brief Split string by delimiter
    /// @param s Input string (modified in place)
    /// @param delim Delimiter string
    /// @param result Output vector of strings
    static void split(const std::string & s, const std::string & delim, std::vector<std::string> & result);

    /// @brief Split string by delimiter
    /// @param str
    /// @param delim
    /// @return
    static std::vector<std::string> split(const std::string & str, char delim);

    /// @brief 读取filepath
    /// @param filepath rpc_manager\client\SERVER_IP.txt
    /// @return 返回ip:port列表
    static std::vector<std::string> getIp(const char * filepath);
};

}  // namespace util
#endif
