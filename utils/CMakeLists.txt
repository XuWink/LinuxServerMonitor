
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(UTILS_SOURCES
    src/ReadFile.cpp
    src/StringUtil.cpp
)

add_library(utils  ${UTILS_SOURCES})
target_link_libraries(utils
    PUBLIC
        logger
)

target_include_directories(utils PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
