#ifndef FACTORY_H
#define FACTORY_H

#include "Item.h"
#include "Actor.h"
#include "Node.h"
#include "Map.h"
#include "Factory_Enums.h"

#include <boost/property_tree/ptree.hpp>

class Factory
{
public:
	Factory();
	~Factory();

	typedef boost::property_tree::ptree 							treeType;
	typedef boost::property_tree::ptree::value_type 	pairType;

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
