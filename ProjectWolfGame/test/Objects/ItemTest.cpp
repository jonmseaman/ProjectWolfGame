#include <boost/test/unit_test.hpp>
#include "Item.h"

BOOST_AUTO_TEST_SUITE(ItemTest)

BOOST_AUTO_TEST_CASE(ConstructorTest) {
  Item i("Item", "Desc", Stats{ 1,2,3 });

  BOOST_REQUIRE_EQUAL(i.getName(), "Item");
  BOOST_REQUIRE_EQUAL(i.getDescription(), "Desc");
  BOOST_REQUIRE(i.stats == Stats(1,2,3));
}

BOOST_AUTO_TEST_CASE(save) {
  Item i("Item", "Desc", Stats{ 1,2,3 });
  i.save();
}

/** Make sure the item is actually used. */
BOOST_AUTO_TEST_CASE(use) {
  // Make sure an item that does damage actually does damage
  // TODO: Write this test
}


BOOST_AUTO_TEST_SUITE_END()
