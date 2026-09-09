cmake_minimum_required(VERSION 4.3.1 FATAL_ERROR)

# The sources use `import std;` and have no header fallback, so this build
# requires a toolchain that can provide the standard library as a module.
#
# `import std;` is behind an experimental gate in CMake, and the gate has to be
# set before the compiler is probed. The value is tied to a CMake release; this
# is the one CMake 4.4 expects. On a CMake that expects a different value the
# gate stays shut and the configure step below fails with an explanation, so
# this value has to be kept current.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

# CMake finds the standard library's module metadata by running the compiler
# with -print-file-name, without any of this project's flags, so it does not
# find a libc++ that is not the compiler's default -- which is exactly the case
# for a Homebrew or self-built LLVM on macOS. Look next to the compiler for it,
# before project() probes the compiler. Passing
# -DCMAKE_CXX_STDLIB_MODULES_JSON=... overrides this.
if(NOT CMAKE_CXX_STDLIB_MODULES_JSON AND CMAKE_CXX_COMPILER)
  get_filename_component(_pwg_compiler_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)
  foreach(_pwg_candidate
      "${_pwg_compiler_dir}/../lib/c++/libc++.modules.json"
      "${_pwg_compiler_dir}/../lib/libc++.modules.json")
    if(EXISTS "${_pwg_candidate}")
      # Normalised rather than resolved, so the path follows a versionless
      # symlink such as /opt/homebrew/opt/llvm and does not pin to a Cellar
      # version that an upgrade will move out from under it.
      cmake_path(SET CMAKE_CXX_STDLIB_MODULES_JSON NORMALIZE "${_pwg_candidate}")
      break()
    endif()
  endforeach()
  unset(_pwg_candidate)
  unset(_pwg_compiler_dir)
endif()

project(ProjectWolfGame CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Everything below depends on `import std;` being available. Fail here with
# something readable rather than letting every source file report that the
# module 'std' was not found.
if(NOT CMAKE_GENERATOR MATCHES "Ninja|Visual Studio")
  message(FATAL_ERROR
    "This project uses `import std;`, which needs a generator that can scan "
    "C++ module dependencies. Re-run with -G Ninja (1.11 or newer) or a "
    "Visual Studio generator.\n"
    "Current generator: ${CMAKE_GENERATOR}")
endif()

set(_pwg_toolchain_detail
  "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} "
  "(${CMAKE_CXX_COMPILER})\n"
  "Standard library: ${CMAKE_CXX_STANDARD_LIBRARY}\n"
  "Module metadata: ${CMAKE_CXX_STDLIB_MODULES_JSON}")

if(NOT CMAKE_CXX_COMPILER_IMPORT_STD)
  message(FATAL_ERROR
    "This project uses `import std;`, which this toolchain cannot provide.\n"
    "It needs a standard library that ships module sources -- a std.cppm and a "
    "libc++.modules.json (or the libstdc++ equivalent).\n"
    ${_pwg_toolchain_detail} "\n"
    "${CMAKE_CXX_COMPILER_IMPORT_STD_ERROR_MESSAGE}")
endif()

# Apple's clang does ship libc++'s module sources, in /usr/share/libc++/v1, so
# the check above passes for it. What it does not ship is clang-scan-deps, and
# without that CMake cannot work out the import graph. Catching it here gives a
# usable message instead of one generate-time error per target.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS)
  message(FATAL_ERROR
    "This project uses `import std;`, and this compiler does not ship "
    "clang-scan-deps, so CMake cannot discover module dependencies. Apple's "
    "clang is the usual case: install an upstream LLVM (brew install llvm) "
    "and point CMAKE_CXX_COMPILER at its clang++.\n"
    ${_pwg_toolchain_detail})
endif()

# The std module is built from the compiler's own libc++, but the linker still
# reaches for the platform's by default. On macOS that means compiling against
# Homebrew's libc++ headers and linking Apple's /usr/lib/libc++.1.dylib, which
# builds and even passes tests while quietly mixing two standard libraries.
# Link against the one the module sources came from.
cmake_path(GET CMAKE_CXX_STDLIB_MODULES_JSON PARENT_PATH _pwg_stdlib_dir)
file(GLOB _pwg_stdlib_libs "${_pwg_stdlib_dir}/libc++.*dylib" "${_pwg_stdlib_dir}/libc++.so*")
if(_pwg_stdlib_libs)
  message(STATUS "import std: linking libc++ from ${_pwg_stdlib_dir}")
  add_link_options("-L${_pwg_stdlib_dir}" "-Wl,-rpath,${_pwg_stdlib_dir}")
endif()
unset(_pwg_stdlib_libs)
unset(_pwg_stdlib_dir)

# Scanning itself needs no target property: CMP0155 is NEW at the
# cmake_minimum_required above.
function(pwg_configure_std target)
  set_target_properties(${target} PROPERTIES CXX_MODULE_STD ON)
endfunction()

message(STATUS "import std: using ${CMAKE_CXX_STDLIB_MODULES_JSON}")

enable_testing()

add_subdirectory(Savable)
add_subdirectory(Engine)
add_subdirectory(ProjectWolfGame)
add_subdirectory(UnitTests)
