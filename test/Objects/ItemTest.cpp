#include "Test.h"
#include "Item.h"

BOOST_AUTO_TEST_SUITE(ItemTest)

Test(ConstructorTest) {
  Item i("Item", "Desc", Stats{ 1,2,3 });

  BOOST_REQUIRE_EQUAL(i.getName(), "Item");
  BOOST_REQUIRE_EQUAL(i.getDescription(), "Desc");
  //BOOST_REQUIRE(i.stats == Stats(1,2,3));
}

Test(save) {
  Item i("Item", "Desc", Stats{ 1,2,3 });
  i.save();
}




BOOST_AUTO_TEST_SUITE_END()