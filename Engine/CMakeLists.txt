add_library(Engine SHARED
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

target_compile_definitions(Engine PRIVATE ENGINE_EXPORTS _WINDOWS _USRDLL)

# PUBLIC so consumers get angle-bracket includes like <Entity/Actor.h>
target_include_directories(Engine PUBLIC "${CMAKE_SOURCE_DIR}/Engine")

# PUBLIC because Engine's own headers expose Savable types
target_link_libraries(Engine PUBLIC Savable)
