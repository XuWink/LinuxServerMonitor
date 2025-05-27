# 指定 CMake 的最低版本要求 
# cmake_minimum_required(VERSION <version>)
cmake_minimum_required(VERSION 3.10)

# 定义项目的名称和使用的编程语言
# project(<project_name> [<language>...])
project(monitor_work LANGUAGES CXX)

add_subdirectory(log_manager)
# add_subdirectory(proto)
add_subdirectory(rpc_manager)
add_subdirectory(display)
add_subdirectory(utils)
add_subdirectory(test)
