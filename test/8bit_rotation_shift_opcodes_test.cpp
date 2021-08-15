//
// Created by cedric on 2021-06-20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EightBitRotationShiftTest

#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "opcode_parsing_math.h"
#include "cpu/CPU.h"
#include "util/testing_utilities.h"

BOOST_AUTO_TEST_SUITE(EightBitRotationShiftTest)

    BOOST_AUTO_TEST_CASE(validate0x80) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x80});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0x81) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x81});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0x82) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x82});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0x83) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x83});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0x84) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x84});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0x85) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x85});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0xAA);
    }
    
BOOST_AUTO_TEST_SUITE_END()