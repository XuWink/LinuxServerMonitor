
find_package(gRPC CONFIG REQUIRED)

set(CLIENT_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RpcClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RpcClientManager.cpp
)

# ###########
# find_package(GTest REQUIRED)
# add_executable(client_exec ${CLIENT_SOURCE})
# target_include_directories(client_exec PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )
# target_link_libraries(client_exec
#     PUBLIC  
#         monitor_proto
#         logger
#         utils
#         gRPC::grpc++ 
#         gRPC::grpc
#         GTest::gtest
#         GTest::gtest_main
# )
# ###########


add_library(client ${CLIENT_SOURCE})
target_include_directories(client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(client
    PUBLIC  
        monitor_proto
        logger
        utils
        gRPC::grpc++ 
        gRPC::grpc

        # GTest::gtest
        # GTest::gtest_main
)