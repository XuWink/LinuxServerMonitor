# cmake_minimum_required(VERSION 3.10)
# project(logger LANGUAGES CXX)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(LOGGER_SOURCE
    logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger_manager.cpp
)

add_library(logger ${LOGGER_SOURCE})

add_executable(logger_app ${LOGGER_SOURCE})

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)