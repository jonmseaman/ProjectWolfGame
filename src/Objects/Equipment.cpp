#include "Equipment.h"
#include "File.h"

pairType Equipment::toTree() {
  return pairType("Equipment", Inventory::toTree().second);
}
