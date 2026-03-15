add_library(Savable SHARED Savable.cpp)

target_compile_definitions(Savable PRIVATE SAVABLE_EXPORTS _WINDOWS _USRDLL)

target_include_directories(Savable PUBLIC "${CMAKE_SOURCE_DIR}/Savable")

target_link_libraries(Savable PRIVATE Boost::filesystem)
