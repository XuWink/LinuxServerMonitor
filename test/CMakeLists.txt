
find_package(GTest REQUIRED)

# 添加可执行程序
add_executable(mytest
  src/main.cpp
)

# 添加头文件目录
target_include_directories(mytest PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接库
target_link_libraries(mytest
  PRIVATE
    GTest::gtest
    GTest::gtest_main
    utils
)
