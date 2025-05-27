cmake_minimum_required(VERSION 3.10)
project(rpc_server LANGUAGES CXX)

# 搜索头文件路径
include_directories(
    ${CMAKE_SOURCE_DIR}/rpc_manager/server/
)
