#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE 8BitLoadTest
#include <boost/test/included/unit_test.hpp>
#include <exception>
#include <unistd.h>

int add(int i, int j)
{
    return i + j;
}

BOOST_AUTO_TEST_SUITE(EightBitLoadTest)

    BOOST_AUTO_TEST_CASE(simplePass)
    {
        BOOST_CHECK(add(2, 2) == 4);
    }
BOOST_AUTO_TEST_SUITE_END()