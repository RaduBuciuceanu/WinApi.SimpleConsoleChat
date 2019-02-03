cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

project(${WASCC_CONSOLE_IO} VERSION ${WASCC_CONSOLE_IO_VERSION})

file(GLOB HEADERS ./include/${WASCC_CONSOLE_IO}/*.h)
file(GLOB SOURCES ./src/${WASCC_CONSOLE_IO}/*.cpp)

add_library(${WASCC_CONSOLE_IO} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${WASCC_CONSOLE_IO} PUBLIC ./include)

target_compile_definitions(${WASCC_CONSOLE_IO} PRIVATE ${WASCC_CONSOLE_IO}=1)