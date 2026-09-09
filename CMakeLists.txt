cmake_minimum_required(VERSION 4.3.1 FATAL_ERROR)

# `import std;` is behind an experimental gate in CMake, and the gate has to be
# set before the compiler is probed. The value is tied to a CMake release; this
# is the one CMake 4.4 expects. A CMake that expects a different value -- older
# or newer -- ignores this, and the build quietly falls back to including
# standard headers. That is safe, but it means `import std` only actually turns
# on under 4.4 until this value is updated. The configure step prints which
# mode it picked.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

project(ProjectWolfGame CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Using `import std;` needs a generator that can scan module dependencies and a
# standard library that ships module sources. Apple's clang ships neither those
# nor clang-scan-deps, and the Makefile generators cannot scan modules, so the
# default build on macOS includes standard headers instead. Both configurations
# have to keep working -- see PWG_IMPORT_STD in the sources. Scanning itself
# needs no target property: CMP0155 is NEW at the cmake_minimum_required above.
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
    "It needs the Ninja or Visual Studio generator and a standard library that "
    "ships module sources (Apple's clang does not).\n"
    "Generator: ${CMAKE_GENERATOR}; compiler: ${CMAKE_CXX_COMPILER_ID} "
    "${CMAKE_CXX_COMPILER_VERSION}")
endif()

# Turns on 'import std' for a target, when it is available.
function(pwg_configure_std target)
  if(PWG_IMPORT_STD)
    set_target_properties(${target} PROPERTIES CXX_MODULE_STD ON)
    target_compile_definitions(${target} PRIVATE PWG_IMPORT_STD=1)
  endif()
endfunction()

message(STATUS "import std: ${PWG_IMPORT_STD}")

enable_testing()

add_subdirectory(Savable)
add_subdirectory(Engine)
add_subdirectory(ProjectWolfGame)
add_subdirectory(UnitTests)
