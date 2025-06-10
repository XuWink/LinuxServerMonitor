# 指定 CMake 的最低版本要求 
cmake_minimum_required(VERSION 3.5)

# 定义项目的名称和使用的编程语言
project(linux_server_monitor LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行文件的保存路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置生成的库文件的保存路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 添加子模块
add_subdirectory(utils)


add_subdirectory(test)

# 启用测试
enable_testing()