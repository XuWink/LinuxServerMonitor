
set(LOGGER_SOURCE
    # logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.cpp
)

add_library(logger ${LOGGER_SOURCE})

# add_executable(logger_app ${LOGGER_SOURCE})

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)