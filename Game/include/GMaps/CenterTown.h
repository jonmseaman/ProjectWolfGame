#ifndef CENTERTOWN_H
#define CENTERTOWN_H
#include "Game.h"
#include "Map.h"
const int CENTER_TOWN_WIDTH{5};

class GAME_API CenterTown : public Maps::Map
{
public:
  CenterTown();
};

#endif
