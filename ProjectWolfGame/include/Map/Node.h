#ifndef NODE_H
#define NODE_H
#include <list>
#include <string>
#include "Inventory.h"
#include "Dir.h"
#include "Savable.h"

class Actor;
namespace Maps
{
  class Node : public File::Savable
  {
    // Temp stuff
    public:
      int getID() { return id; }
      void setID(int idNum) { this->id = idNum; }
      int id;
      pairType toTree();
      void fromTree(const pairType& p);
    public:
      Node();
      virtual ~Node();
      SAVABLE;


      // Data Access
      // Actors

      /**
       * Checks to see if this node contains an Actor
       * @param actor Actor being checked for existence
       * @return True if actor in this
       */
      bool containsActor(Actor* actor);
      /**
       * Returns a pointer to an actor in this.
       * @pre 0 <= index && index <= number of actors in this.
       * @param index The index of the actor being returned.
       * @return A pointer to the actor at position index.
       */
      Actor* getActorPtr(int index);
      /**
       * Returns the next actor in the node's list
       * @param actor The actor which before the one that is returned.
       * @pre There is an actor in this node
       * @return The actor after the actor
       */
      Actor* getNextActor(Actor* actor);

      std::string getName();
      void setName(std::string name) { this->name = name; }
      void setNodeLink(int dir, Node* link);
      /**
       * Allows setting entrance direction for nodes. Nodes can be entered and
       * exited from entrance directions.
       * @pre 0 < dir < Maps::NUM_DIRS
       * @post The node will have an entrance in dir if(isEntrance)
       */
      void setEntranceDir(int dir, bool isEntrance);
      /**
       * The node's inventory. Contains items in the node.
       */
      Inventory inventory;

      // Navigation
      virtual bool isWall() { return false; }
      /**
       * This function is to figure out if moving an actor in a specific
       * direction is possible.
       * @pre 0 <= dir < NUM_DIRS
       * @return True if an actor could move from this int direction dir.
       */
      bool canMoveInDir(int dir);
      /**
       * Allows retrieval of entrance directions on nodes.
       * @param dir The direction being checked.
       * @pre 0 <= dir < NUM_DIRS
       * @return True if the node has an entrance in direction dir.
       */
      bool getEntranceDir(int dir);
      /**
       * Displays a list of nodes that can be traveled to from this node.
       * Shows direction and name of node.
       */
      void showNavigationInfo();
      /**
       * Shows a line of information for a node in a specific direction
       * @usage Used be showNavigationInfo() to display information for eac
       * direction that the player could move in.
       */
      void showNavigationInfoForNode(int dir);

      // Use

      /**
       * Activates the node. This allows all actors in the node to take turns.
       * It also will move actors to other nodes at the end
       */
      virtual void activate();
      /**
       * Adds an actor to the node. The actor is added to the end of the actor
       * list.
       */
      void addActor(Actor *actor);
      /**
       * Moves all actors which have a move direction set.
       */
      void moveActors();
      void removeActor(int index);
      void showActors(); // Shows a list of actors

    protected:
      Node* nodeLinks[NUM_DIRS];
      /// The directions from which this node can be entered
      bool entranceDirs[NUM_DIRS];
      std::list<Actor*> actorPtrList;
      int getNumActors();
      std::string name;
      static int nodeCount;
  };
}

#endif
