#include "read_file.h"

namespace monitor
{
    // 构造函数
    ReadFile::ReadFile(const std::string& file_path) : ifs_(file_path, std::ios::in) {}

    // 析构函数
    ReadFile::~ReadFile()
    {
        std::cout<<"调用ReadFile的析构函数"<<std::endl;
        if(ifs_.is_open())
        {
            ifs_.close();
        }
    }

    bool ReadFile::ReadLine(std::vector<std::string>& args) 
    {
        std::string line;
        if (!std::getline(ifs_, line)) {
            return false;
        }
    
        args.clear();
    
        std::istringstream line_ss(line);
        std::string word;
        while (line_ss >> word) {
            args.push_back(word);
        }
    
        return true;
    }
}