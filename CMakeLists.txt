cmake_minimum_required(VERSION 3.15)

# `import std;` is behind an experimental gate in CMake, and the gate has to be
# set before the compiler is probed. The value identifies a specific CMake
# release; on any other version CMake ignores it and the build falls back to
# including standard headers, so setting it unconditionally is safe.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

project(ProjectWolfGame CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Using `import std;` needs three things at once: a CMake that supports it, a
# generator that can scan module dependencies, and a standard library that
# ships module sources. Apple's clang does not ship them, and the Makefile
# generators cannot scan modules, so the default build on macOS includes
# standard headers instead. Both configurations have to keep working -- see
# PWG_IMPORT_STD in the sources.
set(PWG_IMPORT_STD_DEFAULT OFF)
if(CMAKE_CXX_COMPILER_IMPORT_STD AND CMAKE_GENERATOR MATCHES "Ninja|Visual Studio")
  set(PWG_IMPORT_STD_DEFAULT ON)
endif()
option(PWG_IMPORT_STD
  "Use 'import std;' instead of including standard library headers"
  ${PWG_IMPORT_STD_DEFAULT})

if(PWG_IMPORT_STD AND NOT PWG_IMPORT_STD_DEFAULT)
  message(FATAL_ERROR
    "PWG_IMPORT_STD was requested, but this toolchain cannot provide 'import std'.\n"
    "It needs CMake 3.30+, the Ninja or Visual Studio generator, and a standard "
    "library that ships module sources (Apple's clang does not).\n"
    "Generator: ${CMAKE_GENERATOR}; compiler: ${CMAKE_CXX_COMPILER_ID} "
    "${CMAKE_CXX_COMPILER_VERSION}")
endif()

# Turns on 'import std' for a target, when it is available.
function(pwg_configure_std target)
  if(PWG_IMPORT_STD)
    # CXX_SCAN_FOR_MODULES has to be explicit: policy CMP0155, which would
    # turn scanning on by itself, is OLD under cmake_minimum_required(3.15),
    # and without scanning the compiler never sees the `std` module.
    set_target_properties(${target} PROPERTIES
      CXX_MODULE_STD ON
      CXX_SCAN_FOR_MODULES ON)
    target_compile_definitions(${target} PRIVATE PWG_IMPORT_STD=1)
  endif()
endfunction()

message(STATUS "import std: ${PWG_IMPORT_STD}")

enable_testing()

add_subdirectory(Savable)
add_subdirectory(Engine)
add_subdirectory(ProjectWolfGame)
add_subdirectory(UnitTests)
