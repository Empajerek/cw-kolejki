cmake_minimum_required(VERSION 3.20.0)
project(cw-kolejki VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(cw-kolejki main.cpp kol.cpp)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/@opcjeCpp)
    file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/@opcjeCpp COMPILER_FLAGS)
    target_compile_options(your_executable PRIVATE ${COMPILER_FLAGS})
endif()
