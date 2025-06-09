
cmake_minimum_required(VERSION 3.10)

# project(utils LANGUAGES CXX)

set(SOURCES
    read_file.cpp
)

# 自定义链接库
add_library(utils  ${SOURCES})
target_include_directories(utils PUBLIC include)
