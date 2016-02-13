#include <string>
#include "GObjects\House_2Story.h"
#include "Dir.h"

House_2Story::House_2Story() {
  // Link first and second floor
  setNodeLink(Maps::Up, &secondFloor);
  secondFloor.setNodeLink(Maps::Down, this);
  // Add names to each floor
  setName("House: First Floor");
  secondFloor.setName("House: Second Floor");
  // Set possible entrancesDirs
  for (int i = 0; i < Maps::NUM_DIRS; i++) {
    setEntranceDir(i, true);
    secondFloor.setEntranceDir(i, false);
  }
  setEntranceDir(Maps::Down, false);
  secondFloor.setEntranceDir(Maps::Down, true); // Can only enter second floor from south

}

House_2Story::~House_2Story() {
}

void House_2Story::activate() {
  Node::activate();
  secondFloor.activate();
}
