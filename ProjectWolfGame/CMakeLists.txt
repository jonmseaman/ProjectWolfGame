add_executable(ProjectWolfGame)

target_sources(ProjectWolfGame
  PRIVATE
    FILE_SET CXX_MODULES FILES
      src/Game/Actors/Player.cppm
  PRIVATE
    src/Game/Actors/Player.cpp
    src/Game/Actors/Rat.cpp
    src/Game/Actors/Swordsmen.cpp
    src/Game/Items/BasicSword.cpp
    src/Game/Items/HealingWand.cpp
    src/Game/Maps/CenterTown.cpp
    src/Game/main.cpp
)

pwg_set_warnings(ProjectWolfGame)

target_link_libraries(ProjectWolfGame PRIVATE Engine Savable)
