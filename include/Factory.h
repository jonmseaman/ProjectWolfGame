#ifndef FACTORY_H
#define FACTORY_H

#include "Item.h"
#include "Actor.h"
#include "Node.h"
#include "Map.h"

class Factory
{
public:
	Factory();
	~Factory();

	// Creation functions
	static Item* newItem(int item);
	static Actor* newActor(int actor);
	static Maps::Node* newNode(int node);
	static Maps::Map* newMap(int map);
	/**
	 * This function returns a pointer to the player.
	 * @return Pointer to player.
	 */
	static Actor* getPlayer();
};

// Enums for items, actors, nodes, maps

enum EItems {
	ITEM_BASIC_SWORD,
	ITEM_TYPE_COUNT,
};

enum EActors {
	ACTOR_RAT = 0,
	ACTOR_SWORDSMEN,
	ACTOR_TYPE_COUNT,

};

enum ENodes{
	NODE_HOUSE_2STORY,
	NODE_TYPE_COUNT,
};

enum EMaps{
  MAP_DEFAULT = 0,
  MAP_CENTER_TOWN,
	MAP_TYPE_COUNT,
};

#endif FACTORY_H
