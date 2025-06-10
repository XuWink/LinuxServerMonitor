# 指定 CMake 的最低版本要求 
cmake_minimum_required(VERSION 3.5)

# set(CMAKE_C_COMPILER "D:\\xuwenke\\study_cpp\\mingw64\\bin\\gcc.exe")
# set(CMAKE_CXX_COMPILER "D:\\xuwenke\\study_cpp\\mingw64\\bin\\g++.exe")

# 定义项目的名称和使用的编程语言
project(linux_server_monitor LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行文件的保存路径
# set(EXECUTABLE_OUTPUT_PATH &{PROJECT_SOURCE_DIR}/bin)

# 设置生成的库文件的保存路径
set(LIBARAY_OUTPUT_PATH &{PROJECT_SOURCE_DIR}/lib)

# 添加子模块
add_subdirectory(utils)
# add_subdirectory(log_manager)
# add_subdirectory(rpc_manager)
# add_subdirectory(display)
# add_subdirectory(test)

# 启用测试
enable_testing()