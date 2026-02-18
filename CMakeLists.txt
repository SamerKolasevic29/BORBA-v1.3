cmake_minimum_required(VERSION 3.10)
project(BORBA_v2 VERSION 1.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(include/models)
include_directories(include/views)
include_directories(include/utils)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(borba ${SOURCES})

add_custom_command(TARGET borba POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:borba>/data)

if(WIN32)
    target_link_libraries(borba winmm)
endif()
