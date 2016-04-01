#include <string>
#include <Map/Node.h>
#include <Map/Dir.h>

using namespace Engine::Maps;

class House_2Story : public Node {
public:
  CREATABLE_NODE(House_2Story)
  House_2Story() {
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
  void activate() {
    Node::activate();
    secondFloor.activate();
  }
protected:
private:
  Node secondFloor{};
};
CREATABLE_REGISTRATION(House_2Story);
