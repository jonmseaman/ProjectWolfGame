#ifndef NODE_H
#define NODE_H
#include <list>
#include <string>
#include "Inventory.h"
#include "Actor.h"
#include "NodeData.h"
namespace Maps
{
  class Node : public NodeData
  {
    friend std::ostream &operator<<(std::ostream &os, const Maps::Node &node);
    friend std::istream &operator>>(std::istream &is, Maps::Node &node);
    public:
      static int nodeCount;
      Node();
      virtual ~Node();
      Actor* getActorPtr( int index ); // For getting targets
      Inventory *getInventory(); // Returns a pointer to the nodes inventory
      Actor* getPlayerPtr();
      void giveTarget(Creature* creature);
      virtual void activate();
      bool addActor(Actor *actor);
      void moveActors(); // Tries to move all actors which have a move flag
      bool removeActor(int index);
      std::string getName();
      void setNodeLink(int dir, Node* node);
      void showActors(); // Shows a list of actors
    protected:
      Inventory *inventory;
      Node* nodeLinks[numDirs];
      int getNumActors();
      void updatePlayerPos(int dir);
    private:
      std::list<Actor*> actorPtrList;
      std::string name;
  };
}

// Operators
std::ostream &operator<<(std::ostream &os, const Maps::Node &node);
std::istream &operator>>(std::istream &is, Maps::Node &node);

#endif
