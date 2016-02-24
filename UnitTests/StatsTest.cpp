#include "CppUnitTest.h"
#include "Objects/Stats.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
  TEST_CLASS(StatsTest)
  {
  public:
    
    TEST_METHOD(Constructor)
    {
      Stats s = Stats{ 1,2,3 };
      Assert::AreEqual(1, s.getStamina());
      Assert::AreEqual(2, s.getStrength());
      Assert::AreEqual(3, s.getIntellect());

      s = Stats();
      Assert::AreEqual(0, s.getStamina());
      Assert::AreEqual(0, s.getStrength());
      Assert::AreEqual(0, s.getIntellect());
    }

    TEST_METHOD(additionOperator)
    {
      Stats s = Stats{ 1,2,3 } + Stats{ 3,2,1 };
      Assert::AreEqual(4, s.getStamina());
      Assert::AreEqual(4, s.getStrength());
      Assert::AreEqual(4, s.getIntellect());
    }

    TEST_METHOD(save)
    {
      Stats s{ 1,2,3 };
      for (int i = 0; i < 3; i++) 
      {
        s.save();
      }

      File::save("StatsTest1");
      // Testing to see if save structure was cleared after save
      File::save("StatsTest_EmptyFile");
    }

    TEST_METHOD(File_Load)
    {
      // The two files should be identical
      File::load("StatsTest1");
      File::save("StatsTest1_Copy");
    }

  };
}