
set(MONITOR_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/monitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CpuInfoMonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CpuLoadMonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CpuSoftIrqsMonitor.cpp
)

add_executable(monitor ${MONITOR_SOURCE})
target_include_directories(monitor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(monitor
    PRIVATE
        client
        utils
)