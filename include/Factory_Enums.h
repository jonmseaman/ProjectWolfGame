#ifndef FACTORY_ENUMS_H
#define FACTORY_ENUMS_H
// Enums for items, actors, nodes, maps

enum EItems {
	ITEM_BASIC_SWORD,
	ITEM_HEALING_WAND,
	ITEM_TYPE_COUNT,
};

enum EActors {
	ACTOR_PLAYER = 1,
	ACTOR_RAT,
	ACTOR_SWORDSMEN,
	ACTOR_TYPE_COUNT,

};

enum ENodes {
	NODE_DEFAULT = 0,
	NODE_HOUSE_2STORY,
	NODE_TYPE_COUNT,
};

enum EMaps {
	MAP_DEFAULT = 0,
	MAP_CENTER_TOWN,
	MAP_TYPE_COUNT,
};

#endif
