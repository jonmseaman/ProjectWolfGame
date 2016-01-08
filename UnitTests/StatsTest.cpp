//#include "stdafx.h"
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

  };
}