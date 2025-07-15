# 指定 CMake 的最低版本要求 
cmake_minimum_required(VERSION 3.5)

# 定义项目的名称和使用的编程语言
project(linux_server_monitor LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译为静态库
set(BUILD_SHARED_LIBS OFF)

# 设置静态链接标志
if(WIN32)
  # Windows平台
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STATIC")
else()
  # Linux/Unix平台
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

# 设置可执行文件的保存路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

# 设置生成的库文件的保存路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

# 添加子模块
add_subdirectory(utils)  # 工具模块
add_subdirectory(proto)  # 通信协议模块
add_subdirectory(log_manager)  # 日志管理模块
add_subdirectory(rpc_manager)
add_subdirectory(monitor) # 监测模块
add_subdirectory(display) # 可视化模块
add_subdirectory(unit_test)  # 单元测试模块

# 启用测试
enable_testing()