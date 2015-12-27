#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Entity.h"
#include "Inventory.h"
#include "File.h"
// This function is meant to be a container for equipped items.
#include "File.h"
class ENTITY_API Equipment : public Inventory
{
public:
  pairType toTree();
};

#endif /* end of include guard: EQUIPMENT_H */
