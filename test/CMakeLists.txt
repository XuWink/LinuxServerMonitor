

# 创建测试可执行文件
add_executable(test_main main.cpp)

# 链接 gtest_main 和待测试的 utils 库
target_link_libraries(test_main gtest_main utils)

# 加载 GTest 模块并注册测试
include(GoogleTest)
gtest_discover_tests(test_main)