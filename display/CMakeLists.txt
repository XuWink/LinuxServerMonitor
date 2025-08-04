cmake_minimum_required(VERSION 3.10)

project(display LANGUAGES CXX)

find_package(Qt5
    REQUIRED COMPONENTS
    Core
    Widgets

)

set(DISPLAY_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/display.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QCpuInfoModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QMonitorBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QMonitorMainWidget.cpp
)

add_executable(display ${DISPLAY_SOURCE})
target_include_directories(display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(display
    PRIVATE
        client
        utils
        monitor_proto
        Qt5::Widgets
        Qt5::Core
)