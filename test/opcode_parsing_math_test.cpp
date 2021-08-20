#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE OpcodeParsingTest

#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "opcode_parsing_math.h"

BOOST_AUTO_TEST_SUITE(OpcodeParsingTest)

    BOOST_AUTO_TEST_CASE(validateSwapNibble) {
        BOOST_CHECK(swap_nibble(0x00) == 0x00);
        BOOST_CHECK(swap_nibble(0xFF) == 0xFF);
        BOOST_CHECK(swap_nibble(0xF0) == 0x0F);
        BOOST_CHECK(swap_nibble(0x53) == 0x35);
        BOOST_CHECK(swap_nibble(0x1E) == 0xE1);
    }

    BOOST_AUTO_TEST_CASE(validateByteInRange) {
        BOOST_CHECK(byte_in_range(0x55, 0x50, 0x60));
        BOOST_CHECK(!byte_in_range(0x35, 0x50, 0x60));
        BOOST_CHECK(byte_in_range(0xFF, 0x50, 0xFF));
        BOOST_CHECK(byte_in_range(0x00, 0x00, 0x60));
        BOOST_CHECK(!byte_in_range(0x23, 0xA0, 0xB0));
    }

    BOOST_AUTO_TEST_CASE(byteInRangeExpectError) {
        BOOST_CHECK_THROW(byte_in_range(0x56, 0x36, 0x30), std::runtime_error);
        BOOST_CHECK_THROW(byte_in_range(0x55, 0x55, 0x55), std::runtime_error);
    }

    BOOST_AUTO_TEST_CASE(validateByteInRangeVertical) {
        BOOST_CHECK(byte_in_range_vertical(0x16, 0x06, 0x36));
        BOOST_CHECK(!byte_in_range_vertical(0x17, 0x06, 0x36));
        BOOST_CHECK(!byte_in_range_vertical(0x18, 0x06, 0x36));
        BOOST_CHECK(!byte_in_range_vertical(0x19, 0x06, 0x36));
        BOOST_CHECK(byte_in_range_vertical(0x26, 0x06, 0x36));
        BOOST_CHECK(byte_in_range_vertical(0x36, 0x06, 0x36));
    }

    BOOST_AUTO_TEST_CASE(validateByteInRangeMatrix) {
        BOOST_CHECK(byte_in_range_matrix(0x50, 0x40, 0x65));
        BOOST_CHECK(byte_in_range_matrix(0x51, 0x40, 0x65));
        BOOST_CHECK(!byte_in_range_matrix(0x50, 0x48, 0x6D));
        BOOST_CHECK(!byte_in_range_matrix(0x57, 0x40, 0x65));
        BOOST_CHECK(byte_in_range_matrix(0x01, 0x00, 0x33));
        BOOST_CHECK(!byte_in_range_matrix(0x19, 0x00, 0x33));
    }

BOOST_AUTO_TEST_SUITE_END()