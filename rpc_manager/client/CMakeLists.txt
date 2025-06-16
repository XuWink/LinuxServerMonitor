
set(CLIENT_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RpcClient.cpp
)

add_library(client ${CLIENT_SOURCE})
target_include_directories(client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(client
    PUBLIC  
        monitor_proto
        logger
)