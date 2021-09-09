CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(EMUBOY)


SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Wstrict-aliasing ")
#-pedantic -fmax-errors=5 -Werror -Wunreachable-code -Wcast-align \
##-Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs \
##-Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel \
##-Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses \
##-fdiagnostics-show-option ${CMAKE_CXX_FLAGS}
ENABLE_TESTING()

FIND_PACKAGE(Boost 1.65.1 REQUIRED)

IF (NOT BOOST_FOUND)
    MESSAGE(FATAL_ERROR "BOOST NOT FOUND")
ENDIF ()

FIND_PACKAGE(SDL2 REQUIRED)

IF (NOT SDL2_FOUND)
    MESSAGE(FATAL_ERROR "SDL2 NOT FOUND")
ENDIF ()

FUNCTION(ADD_BOOST_TEST NAME SRC)

    ADD_EXECUTABLE(${NAME} ${SRC})

    TARGET_LINK_LIBRARIES(${NAME} CPU)
    TARGET_INCLUDE_DIRECTORIES(${NAME} PRIVATE ${BOOST_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(${NAME} TEST_UTIL)
    ADD_TEST(NAME ${NAME} COMMAND ${NAME})

ENDFUNCTION()

INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/util)

ADD_LIBRARY(CPU src/cpu/CPU.cpp src/cpu/arithmetic_unit.cpp src/util/opcode_parsing_math.cpp src/video/frame_buffer.cpp src/video/pixel.cpp src/cpu/logic_unit.cpp src/cpu/shifting_unit.cpp src/util/opcode_parsing_8bit_arithmetic.cpp src/util/opcode_parsing_16bit_arithmetic.cpp src/util/opcode_parsing_8bit_rotation_shifts.cpp src/util/opcode_parsing_16bit_lsm.cpp src/util/opcode_parsing_jump_calls.cpp src/util/opcode_parsing_8bit_lsm.cpp src/util/opcode_parsing_16bit_lsm.cpp src/util/opcode_parsing_call_misc.cpp src/cartridge/cartridge_loader.cpp src/cpu/opcode.cpp src/memory_management_unit/memory_management_unit.cpp src/video/color.cpp src/video/palette.cpp)
TARGET_LINK_LIBRARIES(CPU ${BOOST_LIBRARIES})

TARGET_LINK_LIBRARIES(CPU ${SDL2_LIBRARIES})

ADD_EXECUTABLE(EMUBOY src/main.cpp src/video/video.cpp)
TARGET_LINK_LIBRARIES(EMUBOY CPU)

ADD_LIBRARY(TEST_UTIL test/util/testing_utilities.cpp)
TARGET_INCLUDE_DIRECTORIES(TEST_UTIL PRIVATE test/util)
TARGET_LINK_LIBRARIES(TEST_UTIL CPU)

ADD_BOOST_TEST(TEST_SAFETY test/safety_test.cpp)
ADD_BOOST_TEST(TEST_OPCODE_PARSING_MATH test/opcode_parsing_math_test.cpp)
ADD_BOOST_TEST(TEST_8BIT_LSM_OPCODES test/8bit_lsm_opcodes_test.cpp)
ADD_BOOST_TEST(TEST_8BIT_ARITHMETIC_OPCODES test/8bit_arithmetic_opcodes_test.cpp)
ADD_BOOST_TEST(TEST_16BIT_ARITHMETIC_OPCODES test/16bit_arithmetic_opcodes_test.cpp)
ADD_BOOST_TEST(TEST_16BIT_LSM_OPCODES test/16bit_lsm_opcodes_test.cpp)
ADD_BOOST_TEST(TEST_JUMP_CALL_OPCODES test/jump_call_opcodes_test.cpp)
ADD_BOOST_TEST(TEST_8BIT_ROTATIONS_SHIFTS test/8bit_rotation_shift_opcodes_test.cpp)
ADD_BOOST_TEST(TEST_CPU test/cpu_test.cpp)

ADD_CUSTOM_TARGET(TARGET test COMMAND ctest)