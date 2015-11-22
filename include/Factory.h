#ifndef FACTORY_H
#define FACTORY_H

#include "Item.h"
#include "Actor.h"
#include "Node.h"
#include "Map.h"
#include "Factory_Enums.h"

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
	 * If the player does not exist, creates the player.
	 * @return Pointer to player.
	 */
	static Actor* getPlayer();

private:
	static Actor* playerPtr;
};

#endif FACTORY_H
