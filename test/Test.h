#ifndef TEST_H
#define TEST_H
#include <boost/test/unit_test.hpp>

#define Test(n) BOOST_AUTO_TEST_CASE(n)
#define Check(c) BOOST_CHECK(c)
#define Req(c) BOOST_REQUIRE(c)

#endif // TEST_H
