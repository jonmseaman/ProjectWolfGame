include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
    # SYSTEM marks googletest's include directories as system headers for
    # everything that consumes it, so neither the compiler nor an IDE reports
    # problems in code this project does not maintain. EXCLUDE_FROM_ALL keeps
    # its targets out of the default build, so they are built only because
    # UnitTests links them.
    SYSTEM
    EXCLUDE_FROM_ALL
)
# MSVC's default runtime is the DLL CRT, so match it. This is about the C
# runtime, not about how this project's own libraries are linked -- those are
# static.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(UnitTests
    SavableTest.cpp
    SavableErrorTest.cpp
    InputTest.cpp
    EngineTest/CreateTest.cpp
    EngineTest/MemorySafetyTest.cpp
    EngineTest/ItemTest.cpp
    EngineTest/RegistrationTest.cpp
    EngineTest/StatsTest.cpp
    EngineTest/MapTest/MapTest.cpp
    EngineTest/MapTest/NodeTest.cpp
)

target_link_libraries(UnitTests PRIVATE Engine Savable GTest::gtest_main)

pwg_set_warnings(UnitTests)

include(GoogleTest)
gtest_discover_tests(UnitTests)
