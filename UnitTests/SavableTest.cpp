#include "CppUnitTest.h"
#include <string>
#include "Objects/Stats.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
  TEST_CLASS(SavableTest)
  {
  public:

    TEST_METHOD(save_string_string)
    {
      Stats s;

      std::string varName = "StringSave";
      std::string varValue = "StringValue";
      std::string varValueOriginal = varValue;
      s.Savable::save(varName, varValue);
      
      std::string fname = "SavableTest_string_string";
      File::save(fname);
      File::load(fname);

      // Just in case a value isn't actually loaded
      varValue = "";
      s.Savable::load(varName, varValue);

      Assert::AreEqual(varValueOriginal, varValue);
    }

    TEST_METHOD(save_string_int)
    {
      Stats s;

      std::string varName = "StringSave";
      int varValue = 125;
      int varValueOriginal = varValue;
      s.Savable::save(varName, varValue);

      std::string fname = "SavableTest_string_int";
      File::save(fname);
      File::load(fname);

      // Just in case a value isn't actually loaded
      varValue = 0;
      s.Savable::load(varName, varValue);

      Assert::AreEqual(varValueOriginal, varValue);
    }

    /**
    * Makes sure loading and saving is working for many consecutive
    * saves and loads
    */
    TEST_METHOD(stats_load_multipleSavables) 
    {
      const int numSavs = 15;
      Stats s[numSavs];
      Stats loadedStats[numSavs];
      Stats sOriginal[numSavs];
      // Init arrays
      for (int i = 0; i < numSavs; i++) {
        s[i] = Stats{ i + 1, i + 2, i + 3 };
        sOriginal[i] = s[i];
      }

      // Make sure nothing is left over from previous loading / saving
      File::close();

      // Save
      for (auto i = 0; i < numSavs; i++) {
        s[i].save();
      }

      std::string fName = "stats_load_test";
      File::save(fName);
      File::load(fName);

      // Save
      for (auto i = 0; i < numSavs; i++) {
        loadedStats[i].load();
      }

      // Make sure loaded stats are correct
      for (auto i = 0; i < numSavs; i++) {
        Assert::IsTrue(sOriginal[i] == loadedStats[i]);
        Assert::IsTrue(sOriginal[i] == s[i]);
      }
    }
  };
}
