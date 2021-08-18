//
// Created by cedric on 2021-07-25.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EightBitArithmeticTest

#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "cpu/CPU.h"
#include "util/testing_utilities.h"

BOOST_AUTO_TEST_SUITE(EightBitArithmeticTest)

    BOOST_AUTO_TEST_CASE(validate0x04) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_B_INDEX, 0x3E);

        run_next_opcode(&cpu, {0x04});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x3F);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        run_next_opcode(&cpu, {0x04});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x40);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.load_register_immediate(REGISTER_B_INDEX, 0xFF);
        run_next_opcode(&cpu, {0x04});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0x0C) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_C_INDEX, 0x1E);

        run_next_opcode(&cpu, {0x0C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0x1F);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        run_next_opcode(&cpu, {0x0C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0x20);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.load_register_immediate(REGISTER_C_INDEX, 0xFF);
        run_next_opcode(&cpu, {0x0C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0x14) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_D_INDEX, 0x0E);

        run_next_opcode(&cpu, {0x14});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x0F);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        run_next_opcode(&cpu, {0x14});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x10);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.load_register_immediate(REGISTER_D_INDEX, 0xFF);
        run_next_opcode(&cpu, {0x14});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0x1C) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_E_INDEX, 0x9E);

        run_next_opcode(&cpu, {0x1C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0x9F);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        run_next_opcode(&cpu, {0x1C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0xA0);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.load_register_immediate(REGISTER_E_INDEX, 0xFF);
        run_next_opcode(&cpu, {0x1C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0x24) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_H_INDEX, 0x6E);

        run_next_opcode(&cpu, {0x24});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x6F);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        run_next_opcode(&cpu, {0x24});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x70);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.load_register_immediate(REGISTER_H_INDEX, 0xFF);
        run_next_opcode(&cpu, {0x24});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0x37) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        run_next_opcode(&cpu, {0x37});
        BOOST_CHECK(cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0x2C) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xBE);

        run_next_opcode(&cpu, {0x2C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0xBF);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        run_next_opcode(&cpu, {0x2C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0xC0);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.load_register_immediate(REGISTER_L_INDEX, 0xFF);
        run_next_opcode(&cpu, {0x2C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0x34) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.store_memory_immediate(0x21F2, 0xAE);
        cpu.load_16bit_register_immediate(REGISTER_HL_INDEX, 0x21F2);

        run_next_opcode(&cpu, {0x34});
        BOOST_CHECK(cpu.get_byte_memory_indirect(REGISTER_HL_INDEX) == 0xAF);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        run_next_opcode(&cpu, {0x34});
        BOOST_CHECK(cpu.get_byte_memory_indirect(REGISTER_HL_INDEX) == 0xB0);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.store_memory_immediate(0x21F2, 0xFF);
        run_next_opcode(&cpu, {0x34});
        BOOST_CHECK(cpu.get_byte_memory_indirect(REGISTER_HL_INDEX)  == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0x3C) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_A_INDEX, 0x5E);

        run_next_opcode(&cpu, {0x3C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_A_INDEX] == 0x5F);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        run_next_opcode(&cpu, {0x3C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_A_INDEX] == 0x60);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.load_register_immediate(REGISTER_A_INDEX, 0xFF);
        run_next_opcode(&cpu, {0x3C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_A_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

    BOOST_AUTO_TEST_CASE(validate0xF6) {
        CPU cpu;
        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_A_INDEX, 0x00);

        run_next_opcode(&cpu, {0xF6, 0x00});
        BOOST_CHECK(cpu.get_registers()[REGISTER_A_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        set_flags(&cpu, FLAGS_NONE);
        cpu.load_register_immediate(REGISTER_A_INDEX, 0xA3);
        run_next_opcode(&cpu, {0xF6, 0x18});
        BOOST_CHECK(cpu.get_registers()[REGISTER_A_INDEX] == 0xBB);
        BOOST_CHECK(!cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(!cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());

        cpu.load_register_immediate(REGISTER_A_INDEX, 0xFF);
        run_next_opcode(&cpu, {0x3C});
        BOOST_CHECK(cpu.get_registers()[REGISTER_A_INDEX] == 0x00);
        BOOST_CHECK(cpu.is_zero_flag_on());
        BOOST_CHECK(!cpu.is_subtract_flag_on());
        BOOST_CHECK(cpu.is_half_carry_flag_on());
        BOOST_CHECK(!cpu.is_carry_flag_on());
    }

BOOST_AUTO_TEST_SUITE_END()