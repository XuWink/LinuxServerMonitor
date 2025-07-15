#include "StringUtil.hpp"

namespace util {

StringUtil::StringUtil() {}
StringUtil::~StringUtil() {}

void StringUtil::TrimString(std::string& s) {
  s.erase(0, s.find_first_not_of(" \t"));
  s.erase(s.find_last_not_of(" \t") + 1);
}

void StringUtil::split(const std::string& s, const std::string& delim,
                       std::vector<std::string>& result) {
  if (s.empty()) return;

  result.clear();

  int start = 0;
  int end = s.find(delim);

  while (end != std::string::npos) {
    result.emplace_back(s.substr(start, end - start));
    start = end + delim.size();
    end = s.find(delim, start);
  }

  if (start < s.size()) {
    result.emplace_back(s.substr(start));
  }
}

std::vector<std::string> StringUtil::split(const std::string& str, char delim) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream token_stream(str);
  while (std::getline(token_stream, token, delim)) {
    tokens.push_back(token);
  }
  return tokens;
}

}  // namespace util
