#ifndef FACTORY_H
#define FACTORY_H
#include "Factory_Enums.h"
#include "File.h"

class Item;
class Actor;
namespace Maps {
	class Node;
	class Map;
} /* Maps */

#include <boost/property_tree/ptree.hpp>

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
};

#endif FACTORY_H
