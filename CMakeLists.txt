# 指定 CMake 的最低版本要求 
cmake_minimum_required(VERSION 3.10)

# 定义项目的名称和使用的编程语言
project(linux_server_monitor LANGUAGES CXX)

# 添加子模块
add_subdirectory(log_manager)
add_subdirectory(rpc_manager)
add_subdirectory(display)
add_subdirectory(utils)
add_subdirectory(test)
