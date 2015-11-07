#include <iostream>
#include <fstream>
#include "MapManager.h"
#include "utils.h"
#include "dLog.h"
#include "House_2Story.h"

using namespace std;

//TODO: Replace the getInteger funciton with a function which "listens" to the player

int main()
{
  dLog.open("DebugLog.txt", std::fstream::out);
  Maps::Node* node = new House_2Story;
  node->addPlayer();
  while(true)
  {
    node->activate();
  }
  dLog.close();
  return 0;
}
// Extra todos
// TODO: Make a new debug macro
// TODO: Better targeting. No more using pointers.
  // New targeting should specify properties of the target (ie, type, instance#)
  // When a creature want to attack a new target. That creature should send
  // target information and the attack to the node ( or map .) ??
  // OR, could targets be specified as a reference
