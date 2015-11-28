#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <boost/property_tree/ptree.hpp>
#include "Inventory.h"

// This function is meant to be a container for equipped items.

class Equipment : public Inventory
{
public:
  pairType toXML();
};

#endif /* end of include guard: EQUIPMENT_H */
