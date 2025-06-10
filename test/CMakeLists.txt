# 添加模块 test 的头文件搜索路径
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 添加模块 main 的源文件
set(SOURCE
  src/main.cpp
)

# 生成模块 hello 的静态库
# add_library(hello STATIC ${SOURCE})

add_executable(test ${SOURCE})