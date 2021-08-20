#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SafetyTest

#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "util/safety.h"
#include "cpu/CPU.h"
#include "util/testing_utilities.h"

BOOST_AUTO_TEST_SUITE(CPUTest)

    BOOST_AUTO_TEST_CASE(stackTest) {
        CPU cpu;
        cpu.push(0xBEEF);
        cpu.push(0xDEAD);
        cpu.push(0xABCD);

        BOOST_CHECK(cpu.pop() == 0xABCD);
        BOOST_CHECK(cpu.peek() == 0xDEAD);

        cpu.push(0xFEED);

        BOOST_CHECK(cpu.pop() == 0xFEED);
        BOOST_CHECK(cpu.pop() == 0xDEAD);
        BOOST_CHECK(cpu.pop() == 0xBEEF);
    }

    BOOST_AUTO_TEST_CASE(stopTest) {
        CPU cpu;
        BOOST_CHECK(cpu.is_cpu_active());
        BOOST_CHECK(cpu.is_lcd_display_active());
        run_next_opcode(&cpu, {0x10});
        BOOST_CHECK(!cpu.is_cpu_active());
        BOOST_CHECK(!cpu.is_lcd_display_active());
    }

    BOOST_AUTO_TEST_CASE(haltTest) {
        CPU cpu;
        BOOST_CHECK(cpu.is_cpu_active());
        BOOST_CHECK(cpu.is_lcd_display_active());
        run_next_opcode(&cpu, {0x76});
        BOOST_CHECK(!cpu.is_cpu_active());
        BOOST_CHECK(cpu.is_lcd_display_active());
    }

BOOST_AUTO_TEST_SUITE_END()