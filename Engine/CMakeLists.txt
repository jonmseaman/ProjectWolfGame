add_library(Engine SHARED)

target_sources(Engine
  PUBLIC
    FILE_SET CXX_MODULES FILES
      # Partitions, roughly in dependency order.
      Fwd.cppm
      Map/Dir.cppm
      UI/Input.cppm
      Entity/Stats.cppm
      Entity/Item.cppm
      Entity/Inventory.cppm
      Entity/Equipment.cppm
      Entity/Creature.cppm
      Map/Node.cppm
      Entity/Actor.cppm
      Map/Map.cppm
      Map/MapManager.cppm
      Creation/Registration.cppm
      Creation/CreateData.cppm
      Creation/Create.cppm
      # Primary interface unit, which re-exports the partitions.
      Engine.cppm
  PRIVATE
    # Listed so that an IDE associates it with this target. CMake does not
    # compile headers; without this it belongs to no target and shows up as
    # "does not belong to any project target".
    Creation/Creatable.h
    Creation/Create.cpp
    Creation/CreateData.cpp
    Creation/Registration.cpp
    Entity/Actor.cpp
    Entity/Creature.cpp
    Entity/Equipment.cpp
    Entity/Inventory.cpp
    Entity/Item.cpp
    Entity/Stats.cpp
    Map/Dir.cpp
    Map/Map.cpp
    Map/MapManager.cpp
    Map/Node.cpp
    UI/Input.cpp
)

pwg_set_warnings(Engine)

# Consumers get the declarations from `import Engine;`. This is only so they
# can include <Creation/Creatable.h>, which holds the CREATABLE_* macros --
# macros are not exported by modules.
target_include_directories(Engine PUBLIC "${CMAKE_SOURCE_DIR}/Engine")

# PUBLIC because the Engine module re-exports Savable
target_link_libraries(Engine PUBLIC Savable)
