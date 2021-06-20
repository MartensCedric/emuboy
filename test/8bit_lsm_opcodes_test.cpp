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

//struct ManagedCPU {
//    ManagedCPU() = default;
//    ~ManagedCPU() {
//        delete cpu;
//    }
//
//    CPU* get_cpu() const { return cpu; }
//
//    CPU* cpu = new CPU();
//};


BOOST_AUTO_TEST_SUITE(EightBitLSMTest)

    BOOST_AUTO_TEST_CASE(validate0x06)
    {
        CPU cpu;
        run_next_opcode(&cpu, { 0x06, 0x78});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x78);
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

BOOST_AUTO_TEST_SUITE_END()