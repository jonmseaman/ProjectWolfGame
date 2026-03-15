cmake_minimum_required(VERSION 3.15)
project(ProjectWolfGame CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Mirror VS output layout: bin/<arch>/<config>/
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(WG_ARCH "x64")
else()
    set(WG_ARCH "Win32")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${WG_ARCH}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${WG_ARCH}/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${WG_ARCH}/$<CONFIG>")

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
