#include "Equipment.h"

pairType Equipment::toTree() {
  return pairType("Equipment", Inventory::toTree().second);
}
