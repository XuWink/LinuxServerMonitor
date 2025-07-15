
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(UTILS_SOURCES
    src/ReadFile.cpp
    src/StringUtil.cpp
)

add_library(utils  ${UTILS_SOURCES})
# 指定输出目录
# set_target_properties(utils PROPERTIES
#     LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
# )


target_include_directories(utils PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
