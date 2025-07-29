#ifndef READ_FILE_H_
#define READ_FILE_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace util {
class ReadFile {
  public:
    explicit ReadFile(const std::string & file_path);
    ~ReadFile();

    ReadFile & operator=(const ReadFile &) = delete;
    ReadFile(const ReadFile &)             = delete;

    bool ReadLine(std::vector<std::string> & args);

  private:
    std::ifstream ifs_;
};

}  // namespace util

#endif
