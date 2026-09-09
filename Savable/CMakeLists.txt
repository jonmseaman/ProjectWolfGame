add_library(Savable SHARED Savable.cpp)

pwg_set_warnings(Savable)

target_compile_definitions(Savable PRIVATE SAVABLE_EXPORTS _WINDOWS _USRDLL)

target_include_directories(Savable PUBLIC "${CMAKE_SOURCE_DIR}/Savable")

