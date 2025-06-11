

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# 设置 proto 源文件和生成路径
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

set(PROTO_FILES
    ${PROTO_DIR}/monitor.proto
    ${PROTO_DIR}/cpu_info.proto
)

# 获取 gRPC 插件路径
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

# 编译 proto 文件
foreach(proto_file ${PROTO_FILES})
    get_filename_component(proto_name ${proto_file} NAME_WE)

    set(proto_src "${GENERATED_DIR}/${proto_name}.pb.cc")
    set(proto_hdr "${GENERATED_DIR}/${proto_name}.pb.h")
    set(grpc_src "${GENERATED_DIR}/${proto_name}.grpc.pb.cc")
    set(grpc_hdr "${GENERATED_DIR}/${proto_name}.grpc.pb.h")

    add_custom_command(
        OUTPUT ${proto_src} ${proto_hdr} ${grpc_src} ${grpc_hdr}
        COMMAND protobuf::protoc
        ARGS --proto_path=${PROTO_DIR}
             --cpp_out=${GENERATED_DIR}
             --grpc_out=${GENERATED_DIR}
             --plugin=protoc-gen-grpc=${grpc_cpp_plugin_location}
             ${proto_file}
        DEPENDS ${proto_file}
    )

    list(APPEND GENERATED_SRCS ${proto_src} ${grpc_src})
    list(APPEND GENERATED_HDRS ${proto_hdr} ${grpc_hdr})
endforeach()

# 添加生成文件为库
add_library(monitor_proto ${GENERATED_SRCS} ${GENERATED_HDRS})
target_include_directories(monitor_proto PUBLIC ${GENERATED_DIR})
target_link_libraries(monitor_proto
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
