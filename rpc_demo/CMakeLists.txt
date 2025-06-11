cmake_minimum_required(VERSION 3.0)
project(hello_grpc)

set(CMAKE_CXX_STANDARD 11)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${gRPC_INCLUDE_DIRS})

add_executable(server server.cpp hello.pb.cc hello.grpc.pb.cc)
# target_link_libraries(server ${Protobuf_LIBRARIES} ${gRPC_LIBRARIES} ${gRPC_GRPCPP_LIBRARY})

add_executable(client client.cpp hello.pb.cc hello.grpc.pb.cc)
# target_link_libraries(client ${Protobuf_LIBRARIES} ${gRPC_LIBRARIES} ${gRPC_GRPCPP_LIBRARY})
target_link_libraries(server
  PRIVATE
    gRPC::grpc++
    gRPC::grpc
    protobuf::libprotobuf
)

target_link_libraries(client
  PRIVATE
    gRPC::grpc++
    gRPC::grpc
    protobuf::libprotobuf
)