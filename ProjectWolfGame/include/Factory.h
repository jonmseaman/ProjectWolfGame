#ifndef FACTORY_H
#define FACTORY_H
#include "File.h"

class Actor;
class Item;
namespace Maps {
  class Map;
  class Node;
}

class Factory
{
public:
  Factory();
  ~Factory();

  // Creation functions

  // Methods for new saving / loading system
  static Item* loadNewItem();
  static Actor* loadNewActor();
  static Maps::Node* loadNewNode();
  static Maps::Map* loadNewMap();

  // Int id system
  static Item* newItem(int item);
  static Actor* newActor(int actor);
  static Maps::Node* newNode(int node);
  static Maps::Map* newMap(int map);

  // Old LS system
  static Item* newItem(pairType);
  static Actor* newActor(pairType);
  static Maps::Node* newNode(pairType);
  static Maps::Map* newMap(pairType);



  // TODO: Load functions.
  // Functions to load from the file.
  // Must identify what the appropriate type is
};

#endif FACTORY_H
