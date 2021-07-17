//
// Created by cedric on 2021-07-17.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JumpCallTest

#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "opcode_parsing_math.h"
#include "CPU.h"
#include "util/testing_utilities.h"

BOOST_AUTO_TEST_SUITE(JumpCallTest)

    BOOST_AUTO_TEST_CASE(validate0xC7) {
        CPU cpu;
        cpu.jump_to_address(0xF345);
        run_next_opcode(&cpu, {0xC7});
        BOOST_CHECK(cpu.peek() == 0xF345);
        BOOST_CHECK(cpu.get_program_counter() == 0x00);
    }

    BOOST_AUTO_TEST_CASE(validate0xCF) {
        CPU cpu;
        cpu.jump_to_address(0x4D21);
        run_next_opcode(&cpu, {0xCF});
        BOOST_CHECK(cpu.peek() == 0x4D21);
        BOOST_CHECK(cpu.get_program_counter() == 0x08);
    }

    BOOST_AUTO_TEST_CASE(validate0xD7) {
        CPU cpu;
        cpu.jump_to_address(0xE2D2);
        run_next_opcode(&cpu, {0xD7});
        BOOST_CHECK(cpu.peek() == 0xE2D2);
        BOOST_CHECK(cpu.get_program_counter() == 0x10);
    }

    BOOST_AUTO_TEST_CASE(validate0xDF) {
        CPU cpu;
        cpu.jump_to_address(0xBAB4);
        run_next_opcode(&cpu, {0xDF});
        BOOST_CHECK(cpu.peek() == 0xBAB4);
        BOOST_CHECK(cpu.get_program_counter() == 0x18);
    }

    BOOST_AUTO_TEST_CASE(validate0xE7) {
        CPU cpu;
        cpu.jump_to_address(0x24B2);
        run_next_opcode(&cpu, {0xE7});
        BOOST_CHECK(cpu.peek() == 0x24B2);
        BOOST_CHECK(cpu.get_program_counter() == 0x20);
    }

    BOOST_AUTO_TEST_CASE(validate0xEF) {
        CPU cpu;
        cpu.jump_to_address(0x7F2A);
        run_next_opcode(&cpu, {0xEF});
        BOOST_CHECK(cpu.peek() == 0x7F2A);
        BOOST_CHECK(cpu.get_program_counter() == 0x28);
    }

    BOOST_AUTO_TEST_CASE(validate0xF7) {
        CPU cpu;
        cpu.jump_to_address(0x224F);
        run_next_opcode(&cpu, {0xF7});
        BOOST_CHECK(cpu.peek() == 0x224F);
        BOOST_CHECK(cpu.get_program_counter() == 0x30);
    }

    BOOST_AUTO_TEST_CASE(validate0xFF) {
        CPU cpu;
        cpu.jump_to_address(0xACDC);
        run_next_opcode(&cpu, {0xFF});
        BOOST_CHECK(cpu.peek() == 0xACDC);
        BOOST_CHECK(cpu.get_program_counter() == 0x38);
    }

BOOST_AUTO_TEST_SUITE_END()