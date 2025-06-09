#ifndef __READ_FILE__
#define __READ_FILE__

#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
#include <string>

namespace monitor 
{
    class ReadFile
    {
    public:
        explicit ReadFile(const std::string& file_path);
        ~ReadFile();

        ReadFile& operator=(const ReadFile&) = delete;
        ReadFile(const ReadFile&) = delete;

        bool ReadLine(std::vector<std::string>& args);

    private:
        std::ifstream ifs_;
    };

}

#endif