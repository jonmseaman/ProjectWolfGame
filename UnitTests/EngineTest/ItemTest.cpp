#include <string>
#include "CppUnitTest.h"
#include <Entity/Item.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Entity;

namespace UnitTests 
{
  TEST_CLASS(ItemTest)
  {
  public:
    TEST_METHOD(ConstructorTest)
    {
      std::string name = "Item";
      std::string desc = "Desc";
      Stats s = Stats{ 1,2,3 };
       
      Item i(name, desc, s);

      Assert::AreEqual(name, i.getName());
      Assert::AreEqual(desc, i.getDescription());
      Assert::IsTrue(s == i.stats);
    }

    TEST_METHOD(saveAndLoad)
    {
      Item i{ "It", "Desc", Stats{1,2,3} };
      i.save();

      std::string fName = "ItemTest_Save";
      File::save(fName);
      File::load(fName);

      Item otherI;
      otherI.load();

      Assert::IsTrue(i == otherI);
    }
  };

}