cmake_minimum_required(VERSION 3.20.0)
project(cw-kolejki VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_COLOR_DIAGNOSTICS ON)

include(CTest)
enable_testing()

add_executable(cw-kolejki main.cpp kol.cpp)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/opcjeCpp)
    file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/opcjeCpp COMPILER_FLAGS)
    target_compile_options(cw-kolejki PRIVATE ${COMPILER_FLAGS})
endif()

add_test(NAME WSTEP COMMAND cw-kolejki)

add_executable(testy kol_test/tester.cpp kol.cpp)

target_compile_options(testy PRIVATE ${COMPILER_FLAGS})
set(NUMBER_RANGE 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19)

foreach(number ${NUMBER_RANGE})
    add_test(NAME TEST_${number} COMMAND testy ${number})
endforeach()
