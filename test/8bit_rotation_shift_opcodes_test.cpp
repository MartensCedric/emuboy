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

    BOOST_AUTO_TEST_CASE(validate0xCB80) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x80});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB81) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x81});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB82) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x82});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB83) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x83});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB84) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x84});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB85) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xAB);
        run_next_opcode(&cpu, {0xCB, 0x85});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0xAA);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB90) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 0x24);
        run_next_opcode(&cpu, {0xCB, 0x90});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x20);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB91) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0x24);
        run_next_opcode(&cpu, {0xCB, 0x91});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0x20);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB92) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0x24);
        run_next_opcode(&cpu, {0xCB, 0x92});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x20);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB93) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0x24);
        run_next_opcode(&cpu, {0xCB, 0x93});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0x20);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB94) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0x24);
        run_next_opcode(&cpu, {0xCB, 0x94});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x20);
    }

    BOOST_AUTO_TEST_CASE(validate0xCB95) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0x24);
        run_next_opcode(&cpu, {0xCB, 0x95});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0x20);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBA0) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 0x54);
        run_next_opcode(&cpu, {0xCB, 0xA0});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0x44);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBA1) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0x54);
        run_next_opcode(&cpu, {0xCB, 0xA1});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0x44);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBA2) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0x54);
        run_next_opcode(&cpu, {0xCB, 0xA2});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0x44);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBA3) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0x54);
        run_next_opcode(&cpu, {0xCB, 0xA3});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0x44);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBA4) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0x54);
        run_next_opcode(&cpu, {0xCB, 0xA4});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0x44);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBA5) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0x54);
        run_next_opcode(&cpu, {0xCB, 0xA5});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0x44);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBB0) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_B_INDEX, 0xFF);
        run_next_opcode(&cpu, {0xCB, 0xB0});
        BOOST_CHECK(cpu.get_registers()[REGISTER_B_INDEX] == 0xBF);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBB1) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_C_INDEX, 0xFF);
        run_next_opcode(&cpu, {0xCB, 0xB1});
        BOOST_CHECK(cpu.get_registers()[REGISTER_C_INDEX] == 0xBF);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBB2) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_D_INDEX, 0xFF);
        run_next_opcode(&cpu, {0xCB, 0xB2});
        BOOST_CHECK(cpu.get_registers()[REGISTER_D_INDEX] == 0xBF);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBB3) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_E_INDEX, 0xFF);
        run_next_opcode(&cpu, {0xCB, 0xB3});
        BOOST_CHECK(cpu.get_registers()[REGISTER_E_INDEX] == 0xBF);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBB4) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_H_INDEX, 0xFF);
        run_next_opcode(&cpu, {0xCB, 0xB4});
        BOOST_CHECK(cpu.get_registers()[REGISTER_H_INDEX] == 0xBF);
    }

    BOOST_AUTO_TEST_CASE(validate0xCBB5) {
        CPU cpu;
        cpu.load_register_immediate(REGISTER_L_INDEX, 0xFF);
        run_next_opcode(&cpu, {0xCB, 0xB5});
        BOOST_CHECK(cpu.get_registers()[REGISTER_L_INDEX] == 0xBF);
    }

BOOST_AUTO_TEST_SUITE_END()