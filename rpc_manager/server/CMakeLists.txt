
set(SERVER_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RpcServer.cpp
)

add_executable(server ${SERVER_SOURCE})
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(server 
    PUBLIC 
        monitor_proto 
        logger
)
