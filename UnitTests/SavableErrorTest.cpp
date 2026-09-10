#include <gtest/gtest.h>

import std;
import Engine;

using namespace Engine::Entity;

namespace UnitTests {
    /**
     * Regression tests for the save / load failure paths. Each of these used to
     * crash, hang, or silently produce wrong data rather than report a problem.
     */

    // --- Missing / unreadable files (GitHub issue #20) ---

    TEST(SavableErrorTest, loadingMissingFileThrowsInsteadOfCrashing) {
        // File::load used to "succeed" on a file that does not exist, leaving an
        // empty tree that the next nextID() call walked off the end of.
        EXPECT_THROW(File::load("no_such_save_file_at_all"), File::SaveError);
    }

    TEST(SavableErrorTest, nextIdOnEmptyTreeThrowsInsteadOfCrashing) {
        File::clear();
        EXPECT_THROW(File::Savable::nextID("Item"), File::SaveError);
    }

    TEST(SavableErrorTest, startLoadWithNothingToLoadThrows) {
        File::clear();
        Stats s;
        EXPECT_THROW(s.load(), File::SaveError);
    }

    TEST(SavableErrorTest, loadingMissingVariableThrows) {
        File::clear();
        Stats s;
        std::string value;
        EXPECT_THROW(s.Savable::load("neverSaved", value), File::SaveError);
    }

    TEST(SavableErrorTest, loadingNonIntegerAsIntThrows) {
        File::clear();
        Stats s;
        s.Savable::save("notANumber", std::string("twelve"));
        File::save("err_not_an_int");
        File::load("err_not_an_int");

        int value = 0;
        EXPECT_THROW(s.Savable::load("notANumber", value), File::SaveError);
    }

    // --- File name validation ---

    TEST(SavableErrorTest, emptyFileNameIsRejected) {
        EXPECT_THROW(File::save(""), std::invalid_argument);
        EXPECT_THROW(File::load(""), std::invalid_argument);
    }

    TEST(SavableErrorTest, pathTraversalInFileNameIsRejected) {
        // Both directions are validated now; load() used to accept anything.
        EXPECT_THROW(File::save("../escaped"), std::invalid_argument);
        EXPECT_THROW(File::load("../escaped"), std::invalid_argument);
        EXPECT_THROW(File::load("has spaces"), std::invalid_argument);
    }

    // --- Loading twice must not duplicate the tree (GitHub issue #21) ---

    TEST(SavableErrorTest, loadingSameFileTwiceDoesNotDuplicateEntries) {
        File::clear();
        Stats s{1, 2, 3};
        s.save();
        File::save("err_double_load");

        File::load("err_double_load");
        File::load("err_double_load");

        Stats probe;
        int loaded = 0;
        while (probe.canLoad("Stats")) {
            probe.load();
            ++loaded;
        }
        EXPECT_EQ(1, loaded);
    }

    TEST(SavableErrorTest, loadDiscardsAnUnfinishedSave) {
        File::clear();
        // A save that was started but never written to a file must not show up in
        // whatever gets loaded next.
        Stats stranded{9, 9, 9};
        stranded.save();

        Stats onDisk{4, 5, 6};
        File::clear();
        onDisk.save();
        File::save("err_stranded");

        Stats alsoStranded{7, 7, 7};
        alsoStranded.save(); // never saved to a file
        File::load("err_stranded");

        Stats probe;
        int loaded = 0;
        while (probe.canLoad("Stats")) {
            probe.load();
            ++loaded;
        }
        EXPECT_EQ(1, loaded);
    }

    // --- Factory lookups ---

    TEST(SavableErrorTest, unknownIdGivesADescriptiveError) {
        try {
            Creation::Create::newItem("NoSuchItemClass");
            FAIL() << "expected newItem to throw";
        } catch (const std::runtime_error &e) {
            const std::string what = e.what();
            EXPECT_NE(std::string::npos, what.find("NoSuchItemClass"));
            EXPECT_NE(std::string::npos, what.find("Create::newItem"));
        }
    }

    TEST(SavableErrorTest, baseClassesAreRegistered) {
        // A plain Item / Actor / Map saves with an empty id, so the factory has to
        // know how to build one or the object can never be loaded back.
        EXPECT_NE(nullptr, Creation::Create::newItem(""));
        EXPECT_NE(nullptr, Creation::Create::newItem("Item"));
        EXPECT_NE(nullptr, Creation::Create::newActor(""));
        EXPECT_NE(nullptr, Creation::Create::newActor("Actor"));
        EXPECT_NE(nullptr, Creation::Create::newMap(""));
        EXPECT_NE(nullptr, Creation::Create::newMap("Map"));
        EXPECT_NE(nullptr, Creation::Create::newNode(""));
        EXPECT_NE(nullptr, Creation::Create::newNode("Node"));
    }

    TEST(SavableErrorTest, plainItemRoundTripsThroughTheFactory) {
        File::clear();
        Item original{"Trinket", "A small thing", Stats{1, 2, 3}};
        original.save();
        File::save("err_plain_item");
        File::load("err_plain_item");

        auto loaded = Creation::Create::loadNewItem();
        ASSERT_NE(nullptr, loaded);
        EXPECT_EQ("Trinket", loaded->getName());
        EXPECT_EQ("A small thing", loaded->getDescription());
    }

    // --- XML escaping ---

    TEST(SavableErrorTest, markupCharactersSurviveARoundTrip) {
        File::clear();
        Stats s;
        const std::string tricky = "<Rusty> & \"Sharp\" 'Sword' >>";
        s.Savable::save("name", tricky);
        File::save("err_escaping");
        File::load("err_escaping");

        std::string loaded;
        s.Savable::load("name", loaded);
        EXPECT_EQ(tricky, loaded);
    }

    TEST(SavableErrorTest, newlinesSurviveARoundTrip) {
        File::clear();
        Stats s;
        const std::string multiline = "line one\nline two\r\nline three";
        s.Savable::save("description", multiline);
        File::save("err_newlines");
        File::load("err_newlines");

        std::string loaded;
        s.Savable::load("description", loaded);
        EXPECT_EQ(multiline, loaded);
    }

    TEST(SavableErrorTest, escapedEntitiesAreNotUnescapedTwice) {
        File::clear();
        Stats s;
        const std::string literal = "&lt; is how you write &amp;lt;";
        s.Savable::save("text", literal);
        File::save("err_double_escape");
        File::load("err_double_escape");

        std::string loaded;
        s.Savable::load("text", loaded);
        EXPECT_EQ(literal, loaded);
    }

    TEST(SavableErrorTest, markupIsActuallyEscapedOnDisk) {
        File::clear();
        Stats s;
        s.Savable::save("name", std::string("<Sword>"));
        File::save("err_escaping_on_disk");

        std::ifstream f("./Saves/err_escaping_on_disk.xml");
        ASSERT_TRUE(f.is_open());
        const std::string content((std::istreambuf_iterator<char>(f)),
                                  std::istreambuf_iterator<char>());
        EXPECT_NE(std::string::npos, content.find("&lt;Sword&gt;"));
    }

    // --- Item name with markup, end to end through the factory ---

    TEST(SavableErrorTest, itemWithMarkupInItsNameRoundTrips) {
        File::clear();
        Item original{"Sword <of> Ampersand & Co", "5 > 4", Stats{1, 1, 1}};
        original.save();
        File::save("err_item_markup");
        File::load("err_item_markup");

        Item loaded;
        loaded.load();
        EXPECT_EQ("Sword <of> Ampersand & Co", loaded.getName());
        EXPECT_EQ("5 > 4", loaded.getDescription());
    }
} // namespace UnitTests
