//
// Created by cedric on 2021-06-20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SixteenBitLSMTest

#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "opcode_parsing_math.h"
#include "cpu/CPU.h"
#include "util/testing_utilities.h"

BOOST_AUTO_TEST_SUITE(SixteenBitLSMTest)

    BOOST_AUTO_TEST_CASE(validate0x01) {
        CPU cpu;
        run_next_opcode(&cpu, {0x01, 0x80, 0xA1});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_BC_INDEX) == 0xA180);
    }

    BOOST_AUTO_TEST_CASE(validate0x11) {
        CPU cpu;
        run_next_opcode(&cpu, {0x11, 0x07, 0x84});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_DE_INDEX) == 0x8407);
    }

    BOOST_AUTO_TEST_CASE(validate0x21) {
        CPU cpu;
        run_next_opcode(&cpu, {0x21, 0x26, 0x19});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_HL_INDEX) == 0x1926);
    }

    BOOST_AUTO_TEST_CASE(validate0x31) {
        CPU cpu;
        run_next_opcode(&cpu, {0x31, 0x72, 0x27});
        BOOST_CHECK(cpu.get_16bit_register(REGISTER_SP_INDEX) == 0x2772);
    }


BOOST_AUTO_TEST_SUITE_END()