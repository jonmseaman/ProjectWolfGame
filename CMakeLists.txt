cmake_minimum_required(VERSION 3.15)
project(ProjectWolfGame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# TODO(AI): What is this?
set(CMAKE_CXX_EXTENSIONS OFF)

# On non-MSVC, neutralize __declspec(dllexport/dllimport) so the project
# compiles without modifying source files.
if(NOT MSVC)
    add_compile_options(-include "${CMAKE_SOURCE_DIR}/compat/win_compat.h")
endif()

# Boost: read from environment variables (same as VS project)
if(DEFINED ENV{BOOST_ROOT} AND NOT DEFINED BOOST_ROOT)
    set(BOOST_ROOT "$ENV{BOOST_ROOT}")
endif()
if(DEFINED ENV{BOOST_LIBRARYDIR} AND NOT DEFINED BOOST_LIBRARYDIR)
    set(BOOST_LIBRARYDIR "$ENV{BOOST_LIBRARYDIR}")
endif()

# CMake 4.x removed the legacy FindBoost module; prefer config-file mode.
# boost::system became header-only in Boost 1.77 so only filesystem is needed.
cmake_policy(SET CMP0167 NEW)
find_package(Boost 1.90 CONFIG REQUIRED COMPONENTS filesystem)

enable_testing()

add_subdirectory(Savable)
add_subdirectory(Engine)
add_subdirectory(ProjectWolfGame)
add_subdirectory(UnitTests)
