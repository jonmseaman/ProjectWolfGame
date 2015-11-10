#ifndef NODEDATA_H
#define NODEDATA_H
#include <string>
#include "Creature.h"
#include "Dir.h"
namespace Maps
{
  class NodeData
  { // TODO: Virtualize showData() function.
    // TODO: There should be no need for moveLinks[] after a virtualization
    public:
      NodeData();
      //virtual Creature* getActorPtr(int index);
      virtual Inventory* getInventory();
      virtual void giveTarget(Creature *creature);
      void setMoveData(int dir, const std::string &text, NodeData* link);
      void showData();
      virtual void showActors();
    private:
      bool canMoveInDir[numDirs];
      std::string arrMoveText[numDirs];
      NodeData* moveLinks[numDirs];
  };
}
#endif // NODEDATA_H
