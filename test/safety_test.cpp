#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SafetyTest
#include <boost/test/included/unit_test.hpp>
#include <exception>
#include <cpu/CPU.h>
#include "util/safety.h"
#include "util/opcode_parsing_categories.h"

BOOST_AUTO_TEST_SUITE(SafetyTest)

    BOOST_AUTO_TEST_CASE(validateArgumentPass)
    {
        BOOST_CHECK(validate_argument<uint8_t>(0xFF, 0xFF) == 0xFF);
        BOOST_CHECK(validate_argument<uint8_t>(0x25, 0xFF) == 0x25);
        BOOST_CHECK(validate_argument<uint8_t>(0x00, 0x00) == 0x00);
        BOOST_CHECK(validate_argument<uint8_t>(0x5, 0xF) == 0x05);
    }

    BOOST_AUTO_TEST_CASE(validateArgumentExpectError)
    {
        BOOST_CHECK_THROW(validate_argument<uint8_t>(0xFF, 0x34), std::runtime_error);
        BOOST_CHECK_THROW(validate_argument<uint8_t>(0x55, 0x54), std::runtime_error);
        BOOST_CHECK_THROW(validate_argument<uint8_t>(0x38, 0x48), std::runtime_error);
    }

    BOOST_AUTO_TEST_CASE(validateAllOpcodesExists)
    {
        for(uint16_t i = 0; i < 16; i++)
        {
            for(uint16_t j = 0; j < 16; j++)
            {
                uint16_t opcode = (i << 8) + j;
                bool opcode_exists = next_is_misc(opcode);
                opcode_exists = opcode_exists || next_is_jump_calls(opcode);
                opcode_exists = opcode_exists || next_is_16bit_arithmetic(opcode);
                opcode_exists = opcode_exists || next_is_16bit_lsm(opcode);
                opcode_exists = opcode_exists || next_is_8bit_arithmetic(opcode);
                opcode_exists = opcode_exists || next_is_8bit_lsm(opcode);
                opcode_exists = opcode_exists || next_is_8bit_rotation_shifts(opcode);
                BOOST_CHECK(opcode_exists);
            }
        }
    }
BOOST_AUTO_TEST_SUITE_END()