cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

project(${WASCC_IO} VERSION ${WASCC_IO_VERSION})

file(GLOB HEADERS ./include/${WASCC_IO}/*.h)
file(GLOB SOURCES ./src/${WASCC_IO}/*.cpp)

add_library(${WASCC_IO} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${WASCC_IO} PUBLIC ./include)

target_compile_definitions(${WASCC_IO} PRIVATE ${WASCC_IO}=1)