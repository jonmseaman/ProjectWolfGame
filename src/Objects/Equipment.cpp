#include "Equipment.h"
#include "File.h"

pairType Equipment::toXML() {
  return pairType("Equipment", Inventory::toXML().second);
}
