cmake_minimum_required(VERSION 4.3.1 FATAL_ERROR)

# The sources use `import std;` and have no header fallback, so this build
# requires a toolchain that can provide the standard library as a module.
#
# `import std;` is behind an experimental gate in CMake, and the gate has to be
# set before the compiler is probed. The value identifies a CMake release, and
# changes between them, so it has to be picked per version. A value CMake does
# not recognise is ignored silently -- the gate simply stays shut -- which is
# why an unknown version is called out below rather than left to fail
# confusingly further down.
if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.4 AND CMAKE_VERSION VERSION_LESS 4.5)
  set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
elseif(CMAKE_VERSION VERSION_GREATER_EQUAL 4.3 AND CMAKE_VERSION VERSION_LESS 4.4)
  set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
else()
  set(PWG_UNKNOWN_CMAKE_GATE TRUE)
endif()

# CMake finds the standard library's module metadata by running the compiler
# with -print-file-name, without any of this project's flags, so it does not
# find a libc++ that is not the compiler's default -- which is exactly the case
# for a Homebrew or self-built LLVM on macOS. Look next to the compiler for it,
# before project() probes the compiler. Passing
# -DCMAKE_CXX_STDLIB_MODULES_JSON=... overrides this.
#
# This only works when the compiler is known this early, which means it has to
# be passed in -- see CMakePresets.json. An IDE that lets CMake pick the
# compiler itself gets no help from this, and is caught by the checks below.
if(NOT CMAKE_CXX_STDLIB_MODULES_JSON AND CMAKE_CXX_COMPILER)
  cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH _pwg_bin)
  foreach(_pwg_dir "${_pwg_bin}/../lib/c++" "${_pwg_bin}/../lib")
    if(EXISTS "${_pwg_dir}/libc++.modules.json")
      # Normalised, not resolved, so the path follows a versionless symlink
      # such as /opt/homebrew/opt/llvm rather than pinning to a Cellar version
      # that the next upgrade moves.
      cmake_path(SET CMAKE_CXX_STDLIB_MODULES_JSON NORMALIZE
                 "${_pwg_dir}/libc++.modules.json")
      break()
    endif()
  endforeach()
  unset(_pwg_dir)
  unset(_pwg_bin)
endif()

project(ProjectWolfGame CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Report a missing prerequisite once, here, instead of one generate-time error
# per target or a "module 'std' not found" from every source file.
if(NOT CMAKE_GENERATOR MATCHES "Ninja|Visual Studio")
  set(_pwg_problem "the generator cannot scan C++ module dependencies -- use "
                   "-G Ninja (1.11 or newer) or a Visual Studio generator")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS)
  # Checked before the general one below, because a missing scanner is what
  # empties CMAKE_CXX_COMPILER_IMPORT_STD for Apple's clang -- which does ship
  # libc++'s module sources, in /usr/share/libc++/v1. Reporting "no module
  # sources" there would send you looking for the wrong thing.
  set(_pwg_problem "this compiler ships no clang-scan-deps, so CMake cannot "
                   "work out the import graph. Apple's clang is the usual "
                   "case -- including when an IDE picks the compiler for you. "
                   "Install an upstream LLVM (brew install llvm) and point "
                   "CMAKE_CXX_COMPILER at its clang++, or configure with one "
                   "of the presets in CMakePresets.json")
elseif(PWG_UNKNOWN_CMAKE_GATE)
  set(_pwg_problem "`import std` is behind an experimental gate whose value "
                   "changes between CMake releases, and this project does not "
                   "know the value for CMake ${CMAKE_VERSION}. Look for "
                   "CMAKE_EXPERIMENTAL_CXX_IMPORT_STD in that version's "
                   "Help/dev/experimental.rst and add it to CMakeLists.txt")
elseif(NOT CMAKE_CXX_COMPILER_IMPORT_STD)
  set(_pwg_problem "the standard library ships no module sources: a std.cppm "
                   "and a libc++.modules.json, or the libstdc++ equivalent. "
                   "${CMAKE_CXX_COMPILER_IMPORT_STD_ERROR_MESSAGE}")
endif()

if(_pwg_problem)
  message(FATAL_ERROR
    "This project uses `import std;` and has no header fallback, but "
    ${_pwg_problem} ".\n"
    "Generator: ${CMAKE_GENERATOR}\n"
    "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} "
    "(${CMAKE_CXX_COMPILER})\n"
    "Module metadata: ${CMAKE_CXX_STDLIB_MODULES_JSON}")
endif()

# The std module is built from the compiler's own libc++, but the linker still
# reaches for the platform's by default. On macOS that means compiling against
# Homebrew's libc++ headers and linking Apple's /usr/lib/libc++.1.dylib, which
# builds and even passes tests while quietly mixing two standard libraries.
# Link against the one the module sources came from.
cmake_path(GET CMAKE_CXX_STDLIB_MODULES_JSON PARENT_PATH _pwg_stdlib_dir)
file(GLOB _pwg_stdlib_libs "${_pwg_stdlib_dir}/libc++.*dylib" "${_pwg_stdlib_dir}/libc++.so*")
if(_pwg_stdlib_libs)
  add_link_options("-L${_pwg_stdlib_dir}" "-Wl,-rpath,${_pwg_stdlib_dir}")
  message(STATUS "import std: ${CMAKE_CXX_STDLIB_MODULES_JSON}, "
                 "linking libc++ from ${_pwg_stdlib_dir}")
endif()
unset(_pwg_stdlib_libs)
unset(_pwg_stdlib_dir)

# Initialises CXX_MODULE_STD on every target created from here down.
set(CMAKE_CXX_MODULE_STD ON)

option(PWG_WERROR "Treat compiler warnings as errors" OFF)

# Applied per target rather than globally, so that googletest -- which this
# project does not control and which does not build clean -- is left alone.
function(pwg_set_warnings target)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4)
    if(PWG_WERROR)
      target_compile_options(${target} PRIVATE /WX)
    endif()
  else()
    target_compile_options(${target} PRIVATE
      -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic)
    if(PWG_WERROR)
      target_compile_options(${target} PRIVATE -Werror)
    endif()
  endif()
endfunction()

enable_testing()

add_subdirectory(Savable)
add_subdirectory(Engine)
add_subdirectory(ProjectWolfGame)
add_subdirectory(UnitTests)
