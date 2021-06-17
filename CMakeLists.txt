cmake_minimum_required(VERSION 3.17)
project(gameboy)
enable_testing()
function(add_boost_test SOURCE_FILE_NAME DEPENDENCY_LIB)

    get_filename_component(TEST_EXECUTABLE_NAME ${SOURCE_FILE_NAME} NAME_WE)

    add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILE_NAME})
    target_link_libraries(${TEST_EXECUTABLE_NAME}
            ${DEPENDENCY_LIB} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

    file(READ "${SOURCE_FILE_NAME}" SOURCE_FILE_CONTENTS)
    string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\( *([A-Za-z_0-9]+) *\\)"
            FOUND_TESTS ${SOURCE_FILE_CONTENTS})
    foreach(HIT ${FOUND_TESTS})
        string(REGEX REPLACE ".*\\( *([A-Za-z_0-9]+) *\\).*" "\\1" TEST_NAME ${HIT})

        add_test(NAME "${TEST_EXECUTABLE_NAME}.${TEST_NAME}"
                COMMAND ${TEST_EXECUTABLE_NAME}
                --run_test=${TEST_NAME} --catch_system_error=yes)
    endforeach()
endfunction()

FIND_PACKAGE(Boost 1.65.1 COMPONENTS unit_test_framework REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 20)

add_library(gameboy src/main.cpp src/CPU.cpp include/CPU.h)

TARGET_LINK_LIBRARIES(gameboy LINK_PUBLIC ${Boost_LIBRARIES})

add_executable(8bit_load_test test/8bit_loads_test.cpp)

target_include_directories(8bit_load_test PRIVATE ${BOOST_INCLUDE_DIRS})
add_test(NAME 8bit_load COMMAND 8bit_load_test)