add_library(Savable SHARED)

target_sources(Savable
  PUBLIC
    FILE_SET CXX_MODULES FILES
      Savable.cppm
  PRIVATE
    # Listed so that an IDE associates it with this target; CMake does not
    # compile headers.
    SavableMacros.h
    Savable.cpp)

pwg_set_warnings(Savable)

target_compile_definitions(Savable PRIVATE SAVABLE_EXPORTS _WINDOWS _USRDLL)

# Only for SavableMacros.h; the declarations come from `import Savable;`.
target_include_directories(Savable PUBLIC "${CMAKE_SOURCE_DIR}/Savable")

