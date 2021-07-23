//
// Created by cedric on 2021-06-20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SixteenBitArithmeticTest

#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "opcode_parsing_math.h"
#include "cpu/CPU.h"
#include "util/testing_utilities.h"

BOOST_AUTO_TEST_SUITE(SixteenBitArithmeticTest)

    BOOST_AUTO_TEST_CASE(validate0x03) {
        CPU cpu;
        cpu.load_16bit_register_immediate(REGISTER_BC_INDEX, 0x4F2F);
        run_next_opcode(&cpu, {0x03});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_BC_INDEX) == 0x4F30);

        cpu.load_16bit_register_immediate(REGISTER_BC_INDEX, 0xFFFF);
        run_next_opcode(&cpu, {0x03});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_BC_INDEX) == 0x0000);
    }

    BOOST_AUTO_TEST_CASE(validate0x13) {
        CPU cpu;
        cpu.load_16bit_register_immediate(REGISTER_DE_INDEX, 0x2132);
        run_next_opcode(&cpu, {0x13});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_DE_INDEX) == 0x2133);

        cpu.load_16bit_register_immediate(REGISTER_DE_INDEX, 0xFFFF);
        run_next_opcode(&cpu, {0x13});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_DE_INDEX) == 0x0000);
    }

    BOOST_AUTO_TEST_CASE(validate0x23) {
        CPU cpu;
        cpu.load_16bit_register_immediate(REGISTER_HL_INDEX, 0x1E71);
        run_next_opcode(&cpu, {0x23});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_HL_INDEX) == 0x1E72);

        cpu.load_16bit_register_immediate(REGISTER_HL_INDEX, 0xFFFF);
        run_next_opcode(&cpu, {0x23});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_HL_INDEX) == 0x0000);
    }

    BOOST_AUTO_TEST_CASE(validate0x33) {
        CPU cpu;
        cpu.load_16bit_register_immediate(REGISTER_SP_INDEX, 0x62F1);
        run_next_opcode(&cpu, {0x23});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_SP_INDEX) == 0x62F2);

        cpu.load_16bit_register_immediate(REGISTER_SP_INDEX, 0xFFFF);
        run_next_opcode(&cpu, {0x23});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_SP_INDEX) == 0x0000);
    }

    BOOST_AUTO_TEST_CASE(validate0x0B) {
        CPU cpu;
        cpu.load_16bit_register_immediate(REGISTER_BC_INDEX, 0x4F2F);
        run_next_opcode(&cpu, {0x0B});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_BC_INDEX) == 0x4F2E);

        cpu.load_16bit_register_immediate(REGISTER_BC_INDEX, 0x0000);
        run_next_opcode(&cpu, {0x0B});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_BC_INDEX) == 0xFFFF);
    }

    BOOST_AUTO_TEST_CASE(validate0x1B) {
        CPU cpu;
        cpu.load_16bit_register_immediate(REGISTER_DE_INDEX, 0x2132);
        run_next_opcode(&cpu, {0x1B});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_DE_INDEX) == 0x2131);

        cpu.load_16bit_register_immediate(REGISTER_DE_INDEX, 0x0000);
        run_next_opcode(&cpu, {0x1B});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_DE_INDEX) == 0xFFFF);
    }

    BOOST_AUTO_TEST_CASE(validate0x2B) {
        CPU cpu;
        cpu.load_16bit_register_immediate(REGISTER_HL_INDEX, 0x1E71);
        run_next_opcode(&cpu, {0x2B});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_HL_INDEX) == 0x1E70);

        cpu.load_16bit_register_immediate(REGISTER_HL_INDEX, 0x0000);
        run_next_opcode(&cpu, {0x2B});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_HL_INDEX) == 0xFFFF);
    }

    BOOST_AUTO_TEST_CASE(validate0x3B) {
        CPU cpu;
        cpu.load_16bit_register_immediate(REGISTER_SP_INDEX, 0x62F1);
        run_next_opcode(&cpu, {0x3B});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_SP_INDEX) == 0x62F0);

        cpu.load_16bit_register_immediate(REGISTER_SP_INDEX, 0x0000);
        run_next_opcode(&cpu, {0x3B});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_SP_INDEX) == 0xFFFF);
    }

BOOST_AUTO_TEST_SUITE_END()