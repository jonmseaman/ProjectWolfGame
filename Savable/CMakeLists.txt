add_library(Savable SHARED)

target_sources(Savable
  PUBLIC
    FILE_SET CXX_MODULES FILES
      Savable.cppm
  PRIVATE
    Savable.cpp)

pwg_set_warnings(Savable)

target_compile_definitions(Savable PRIVATE SAVABLE_EXPORTS _WINDOWS _USRDLL)

# Only for SavableMacros.h; the declarations come from `import Savable;`.
target_include_directories(Savable PUBLIC "${CMAKE_SOURCE_DIR}/Savable")

