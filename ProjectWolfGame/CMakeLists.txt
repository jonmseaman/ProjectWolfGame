add_executable(ProjectWolfGame
    src/Game/Actors/Player.cpp
    src/Game/Actors/Rat.cpp
    src/Game/Actors/Swordsmen.cpp
    src/Game/Items/BasicSword.cpp
    src/Game/Items/HealingWand.cpp
    src/Game/Maps/CenterTown.cpp
    src/Game/main.cpp
)

# Mirror VS naming: ProjectWolfGame_Debug.exe / ProjectWolfGame_Release.exe
set_target_properties(ProjectWolfGame PROPERTIES
    OUTPUT_NAME "ProjectWolfGame_$<CONFIG>"
)

target_link_libraries(ProjectWolfGame PRIVATE Engine Savable)
