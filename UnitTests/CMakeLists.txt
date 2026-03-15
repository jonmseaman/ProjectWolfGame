include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# Use shared CRT to match the rest of the project on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(UnitTests
    SavableTest.cpp
    EngineTest/CreateTest.cpp
    EngineTest/ItemTest.cpp
    EngineTest/RegistrationTest.cpp
    EngineTest/StatsTest.cpp
    EngineTest/MapTest/MapTest.cpp
    EngineTest/MapTest/NodeTest.cpp
)

target_link_libraries(UnitTests PRIVATE Engine Savable GTest::gtest_main)

# On macOS, embed @loader_path so the test binary finds Savable/Engine dylibs
# in the same output directory without needing DYLD_LIBRARY_PATH at runtime.
if(APPLE)
    set_target_properties(UnitTests PROPERTIES
        BUILD_RPATH "@loader_path"
    )
    set_target_properties(Engine PROPERTIES
        BUILD_RPATH "@loader_path"
    )
endif()

include(GoogleTest)
gtest_discover_tests(UnitTests)
