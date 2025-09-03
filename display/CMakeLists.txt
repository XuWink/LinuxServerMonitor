cmake_minimum_required(VERSION 3.10)

project(display LANGUAGES CXX)

find_package(Qt5
    REQUIRED COMPONENTS
    Core
    Widgets
)

set(CMAKE_AUTOMOC ON)  # 启用自动 moc
set(CMAKE_AUTOUIC ON)   # 如果用 ui
# set(CMAKE_AUTORCC ON)   # 如果用 qrc

set(DISPLAY_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QMonitorBase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QCpuInfoModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QCpuLoadModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QCpuSoftIrqsModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QMemInfoModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QNetInfoModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QMonitorMainWidget.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Worker.hpp
)

set(DISPLAY_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/display.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Worker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QCpuInfoModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QCpuLoadModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QCpuSoftIrqsModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QMemInfoModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QNetInfoModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QMonitorBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QMonitorMainWidget.cpp
)

add_executable(display ${DISPLAY_SOURCE} ${DISPLAY_HEADER})
target_include_directories(display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(display
    PRIVATE
        client
        utils
        monitor_proto
        Qt5::Widgets
        Qt5::Core
)