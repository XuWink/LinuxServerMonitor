# 查找并加载 Protobuf 和 gRPC 的 CMake 配置
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(c-ares CONFIG)

# Protobuf/Grpc source files
set(PROTO_FILES
    monitor.proto
    cpu_info.proto
)

# 设置生成文件的输出目录
set(GENERATED_DIR "${PROJECT_SOURCE_DIR}/proto/generated")

# 创建库目标
add_library(monitor_proto ${PROTO_FILES})

# 链接库
target_link_libraries(monitor_proto
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

# 设置包含目录
target_include_directories(monitor_proto PUBLIC
    ${PROTOBUF_INCLUDE_DIRS}
    ${GENERATED_DIR}  # 添加生成的目录到包含路径
)

# 获取 gRPC C++ 插件的位置
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

# 生成 C++ 代码
protobuf_generate_cpp(
    TARGET monitor_proto
    LANGUAGE cpp
    PROTO_FILES ${PROTO_FILES}
    OUT ${GENERATED_DIR}  # 指定生成文件的输出目录
)

# 生成 gRPC 代码
protobuf_generate_grpc(
    TARGET monitor_proto
    LANGUAGE grpc
    PROTO_FILES ${PROTO_FILES}
    OUT ${GENERATED_DIR}  # 指定生成文件的输出目录
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)