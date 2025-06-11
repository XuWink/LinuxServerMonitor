#include <gtest/gtest.h>

#include "read_file.h"

bool test_readfile(const std::string &file_path) 
{
    // 读取文件
    monitor::ReadFile reader(file_path);
    std::vector<std::string> lines;
    if (reader.ReadLine(lines)) {
        for (const auto& line : lines) {
            std::cout << line <<'\t';
        }
    } else {
        return false;
    }

    return true;
}

// 简单测试用例
TEST(ReadLineTest, ReadLineTest) {
    EXPECT_EQ(test_readfile("../assets/test.txt"), true);
    EXPECT_EQ(test_readfile("test2.txt"), false);
}