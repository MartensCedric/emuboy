//
// Created by cedric on 2021-06-20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EightBitLSMTest
#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "opcode_parsing_math.h"
#include "CPU.h"
#include "util/testing_utilities.h"

BOOST_AUTO_TEST_SUITE(EightBitLSMTest)

    BOOST_AUTO_TEST_CASE(validate0x02)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 0x4F);
        cpu.load_register_immediate(REGISTER_C_INDEX, 0x23);
        cpu.load_register_immediate(REGISTER_A_INDEX, 0x22);
        run_next_opcode(&cpu, { 0x02});
        cpu.load_memory_indirect(REGISTER_H_INDEX, 0x4F23);
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x22);
    }

    BOOST_AUTO_TEST_CASE(validate0x06)
    {
        CPU cpu;
        run_next_opcode(&cpu, { 0x06, 0x78});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x78);
    }

    BOOST_AUTO_TEST_CASE(validate0x12)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0x62);
        cpu.load_register_immediate(REGISTER_E_INDEX, 0x1F);
        cpu.load_register_immediate(REGISTER_A_INDEX, 0x8F);
        run_next_opcode(&cpu, { 0x12});
        cpu.load_memory_indirect(REGISTER_H_INDEX, 0x621F);
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x8F);
    }


    BOOST_AUTO_TEST_CASE(validate0x16)
    {
        CPU cpu;
        run_next_opcode(&cpu, { 0x16, 0x33});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x33);
    }

    BOOST_AUTO_TEST_CASE(validate0x26)
    {
        CPU cpu;
        run_next_opcode(&cpu, { 0x26, 0xA3});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0xA3);
    }

    BOOST_AUTO_TEST_CASE(validate0x0E)
    {
        CPU cpu;
        run_next_opcode(&cpu, { 0x0E, 0x72});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0x72);
    }

    BOOST_AUTO_TEST_CASE(validate0x1E)
    {
        CPU cpu;
        run_next_opcode(&cpu, { 0x1E, 0x92});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0x92);
    }

    BOOST_AUTO_TEST_CASE(validate0x2E)
    {
        CPU cpu;
        run_next_opcode(&cpu, { 0x2E, 0x03});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0x03);
    }

    BOOST_AUTO_TEST_CASE(validate0x3E)
    {
        CPU cpu;
        run_next_opcode(&cpu, { 0x3E, 0x45});
        BOOST_CHECK(cpu.get_registers()[REGISTER_A_INDEX] == 0x45);
    }

    BOOST_AUTO_TEST_CASE(validate0x40)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 5);
        run_next_opcode(&cpu, { 0x40 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 5);
    }

    BOOST_AUTO_TEST_CASE(validate0x41)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0xE1);
        run_next_opcode(&cpu, { 0x41 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0xE1);
    }

    BOOST_AUTO_TEST_CASE(validate0x42)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0x31);
        run_next_opcode(&cpu, { 0x42 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x31);
    }

    BOOST_AUTO_TEST_CASE(validate0x43)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0x19);
        run_next_opcode(&cpu, { 0x43 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x19);
    }

    BOOST_AUTO_TEST_CASE(validate0x44)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0x72);
        run_next_opcode(&cpu, { 0x44 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x72);
    }

    BOOST_AUTO_TEST_CASE(validate0x45)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xAE);
        run_next_opcode(&cpu, { 0x45 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0xAE);
    }

    BOOST_AUTO_TEST_CASE(validate0x46)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0xF2);
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xAE);
        cpu.store_memory_immediate(0xF2AE, 0x74);
        run_next_opcode(&cpu, { 0x46 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x74);
    }

    BOOST_AUTO_TEST_CASE(validate0x47)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_A_INDEX, 0x4D);
        run_next_opcode(&cpu, { 0x47 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x4D);
    }

    BOOST_AUTO_TEST_CASE(validate0x48)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 0x3E);
        run_next_opcode(&cpu, { 0x48 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0x3E);
    }

    BOOST_AUTO_TEST_CASE(validate0x49)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0x0F);
        run_next_opcode(&cpu, { 0x49 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0x0F);
    }


    BOOST_AUTO_TEST_CASE(validate0x4A)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0xB3);
        run_next_opcode(&cpu, { 0x4A });
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0xB3);
    }

    BOOST_AUTO_TEST_CASE(validate0x4B)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0xC7);
        run_next_opcode(&cpu, { 0x4B });
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0xC7);
    }

    BOOST_AUTO_TEST_CASE(validate0x4C)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0xFA);
        run_next_opcode(&cpu, { 0x4C });
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0xFA);
    }

    BOOST_AUTO_TEST_CASE(validate0x4D)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xCF);
        run_next_opcode(&cpu, { 0x4D });
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0xCF);
    }

    BOOST_AUTO_TEST_CASE(validate0x50)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 5);
        run_next_opcode(&cpu, { 0x50 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 5);
    }

    BOOST_AUTO_TEST_CASE(validate0x51)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0xE1);
        run_next_opcode(&cpu, { 0x51 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0xE1);
    }

    BOOST_AUTO_TEST_CASE(validate0x52)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0x31);
        run_next_opcode(&cpu, { 0x52 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x31);
    }

    BOOST_AUTO_TEST_CASE(validate0x53)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0x19);
        run_next_opcode(&cpu, { 0x53 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x19);
    }

    BOOST_AUTO_TEST_CASE(validate0x54)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0x72);
        run_next_opcode(&cpu, { 0x54 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x72);
    }

    BOOST_AUTO_TEST_CASE(validate0x55)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xAE);
        run_next_opcode(&cpu, { 0x55 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0xAE);
    }

    BOOST_AUTO_TEST_CASE(validate0x56)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0xA1);
        cpu.load_register_immediate(REGISTER_L_INDEX, 0x37);
        cpu.store_memory_immediate(0xA137, 0x5F);
        run_next_opcode(&cpu, { 0x56 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x5F);
    }

    BOOST_AUTO_TEST_CASE(validate0x60)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 5);
        run_next_opcode(&cpu, { 0x60 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 5);
    }

    BOOST_AUTO_TEST_CASE(validate0x61)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0xE1);
        run_next_opcode(&cpu, { 0x61 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0xE1);
    }

    BOOST_AUTO_TEST_CASE(validate0x62)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0x31);
        run_next_opcode(&cpu, { 0x62 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x31);
    }

    BOOST_AUTO_TEST_CASE(validate0x63)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0x19);
        run_next_opcode(&cpu, { 0x63 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x19);
    }

    BOOST_AUTO_TEST_CASE(validate0x64)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0x72);
        run_next_opcode(&cpu, { 0x64 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x72);
    }

    BOOST_AUTO_TEST_CASE(validate0x65)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xAE);
        run_next_opcode(&cpu, { 0x65 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0xAE);
    }

    BOOST_AUTO_TEST_CASE(validate0x66)
    {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0x03);
        cpu.load_register_immediate(REGISTER_L_INDEX, 0x16);
        cpu.store_memory_immediate(0x0316, 0x7A);
        run_next_opcode(&cpu, { 0x66 });
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x7A);
    }


BOOST_AUTO_TEST_SUITE_END()