#ifndef CREATE_H
#define CREATE_H

class Actor;
class Item;
namespace Engine {
namespace Maps {
  class Map;
  class Node;
}
}

using namespace Engine::Maps;

class Create
{
public:
  Create();
  ~Create();

  // Creation functions

  // Methods for new saving / loading system
  static Item* loadNewItem();
  static Actor* loadNewActor();
  static Node* loadNewNode();
  static Map* loadNewMap();

  // Int id system
  static Item* newItem(int item);
  static Actor* newActor(int actor);
  static Node* newNode(int node);
  static Map* newMap(int map);
};

#endif CREATE_H
