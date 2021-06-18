#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SafetyTest
#include <boost/test/included/unit_test.hpp>
#include <exception>
#include "util/safety.h"

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
BOOST_AUTO_TEST_SUITE_END()