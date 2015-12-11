#ifndef FACTORY_H
#define FACTORY_H

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
  /**
   * For parameters of type pairType, the pair must be a valid xml pair
   * for that type
   */

  static Item* newItem(int item);
  static Item* newItem(pairType);
  static Actor* newActor(int actor);
  static Actor* newActor(pairType);
  static Maps::Node* newNode(int node);
  static Maps::Node* newNode(pairType);
  static Maps::Map* newMap(int map);
  static Maps::Map* newMap(pairType);

  // TODO: Load functions.
  // Functions to load from the file.
  // Must identify what the appropriate type is
};

#endif FACTORY_H
