#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Inventory.h"

// This class is meant to be a container for equipped items.

class Equipment : public Inventory
{
public:
  pairType toTree();
};

#endif /* end of include guard: EQUIPMENT_H */
