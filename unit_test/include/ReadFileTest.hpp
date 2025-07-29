#include "ReadFile.hpp"

#include <gtest/gtest.h>

bool TestReadFile(const std::string & file_path, std::string * error_msg = nullptr) {
    util::ReadFile           reader(file_path);
    std::vector<std::string> lines;
    if (!reader.ReadLine(lines)) {
        if (error_msg) {
            *error_msg = "Failed to read file: " + file_path;
        }
        return false;
    }
    if (lines.empty()) {
        if (error_msg) {
            *error_msg = "File is empty: " + file_path;
        }
        return false;
    }
    return true;
}

// 测试用例
TEST(ReadFileTest, ReadExistingFile) {
    std::string error_msg;
    bool        success = TestReadFile("../assets/test.txt", &error_msg);
    EXPECT_TRUE(success) << error_msg;  // 输出错误信息
}

TEST(ReadFileTest, ReadNonexistentFile) {
    std::string error_msg;
    bool        success = TestReadFile("../assets/test2.txt", &error_msg);
    EXPECT_FALSE(success) << "Expected failure for nonexistent file, but got success";
}
