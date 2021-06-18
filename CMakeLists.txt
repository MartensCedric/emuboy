cmake_minimum_required(VERSION 3.17)
project(gameboy)
enable_testing()

FIND_PACKAGE(Boost 1.65.1 COMPONENTS unit_test_framework REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()
set(CMAKE_CXX_STANDARD 20)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})


INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/opcodes)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/util)

ADD_LIBRARY(cpu src/CPU.cpp src/opcodes/8bit_load_opcodes.cpp)

TARGET_LINK_LIBRARIES(cpu ${Boost_LIBRARIES})

add_executable(gameboy src/main.cpp)

TARGET_LINK_LIBRARIES(gameboy cpu)

add_executable(safety_test test/safety_test.cpp)

target_link_libraries(safety_test cpu)
target_include_directories(safety_test PRIVATE ${BOOST_INCLUDE_DIRS})
add_test(NAME test_safety COMMAND safety_test)