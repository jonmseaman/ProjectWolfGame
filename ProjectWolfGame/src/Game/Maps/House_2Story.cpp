#include <string>
#include "GObjects\House_2Story.h"
#include "Dir.h"

using namespace Engine::Maps;

House_2Story::House_2Story() {
  // Link first and second floor
  setNodeLink(UP, &secondFloor);
  secondFloor.setNodeLink(DOWN, this);
  // Add names to each floor
  setName("House: First Floor");
  secondFloor.setName("House: Second Floor");
  // Set possible entrancesDirs
  for (int i = 0; i < NUM_DIRS; i++) {
    setEntranceDir(i, true);
    secondFloor.setEntranceDir(i, false);
  }
  setEntranceDir(DOWN, false);
  secondFloor.setEntranceDir(DOWN, true); // Can only enter second floor from south

}

House_2Story::~House_2Story() {
}

void House_2Story::activate() {
  Node::activate();
  secondFloor.activate();
}
