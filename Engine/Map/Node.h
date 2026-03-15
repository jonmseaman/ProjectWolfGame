#ifndef NODE_H
#define NODE_H
#include <Engine.h>
#include <array>
#include <atomic>
#include <list>
#include <memory>
#include <string>
#include "Entity/Inventory.h"
#include "Dir.h"
#include "Savable.h"

namespace Engine {
namespace Entity {
class Actor;
}
namespace Maps
{
  class ENGINE_API Node : public File::Savable
  {
    public:
      Node();
      virtual ~Node();
      SAVABLE_CLEAR;


      // Data Access
      // Actors

      /**
       * Checks to see if this node contains an Actor
       * @param actor Actor being checked for existence
       * @return True if actor in this
       */
      bool containsActor(Engine::Entity::Actor* actor);
      /**
       * Returns a pointer to an actor in this.
       * @pre 0 <= index && index <= number of actors in this.
       * @param index The index of the actor being returned.
       * @return A pointer to the actor at position index.
       */
      Engine::Entity::Actor* getActorPtr(int index);
      /**
       * Returns the next actor in the node's list
       * @param actor The actor which before the one that is returned.
       * @pre There is an actor in this node
       * @return The actor after the actor
       */
      Engine::Entity::Actor* getNextActor(Engine::Entity::Actor* actor);

      void setNodeLink(Dir dir, Node* link);
      /**
       * Allows setting entrance direction for nodes. Nodes can be entered and
       * exited from entrance directions.
       * @post The node will have an entrance in dir if(isEntrance)
       */
      void setEntranceDir(Dir dir, bool isEntrance);
      /**
       * The node's inventory. Contains items in the node.
       */
      Engine::Entity::Inventory inventory;

      // Navigation
      virtual bool isWall() const { return false; }
      /**
       * Returns true if an actor can move from this node in direction dir.
       */
      bool canMoveInDir(Dir dir) const;
      /**
       * Returns true if the node has an entrance in direction dir.
       */
      bool getEntranceDir(Dir dir) const;
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
      void showNavigationInfoForNode(Dir dir);

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
      void addActor(std::unique_ptr<Engine::Entity::Actor> actor);
      int getNumActors() const;
      /**
       * Moves all actors which have a move direction set.
       */
      void moveActors();
      void showActors(); // Shows a list of actors

      std::string getName() const;
      void setName(std::string name) { this->name = name; }

      std::list<std::unique_ptr<Engine::Entity::Actor>> actorPtrs;

    protected:
      std::array<Node*, NUM_DIRS> nodeLinks;
      /// The directions from which this node can be entered
      std::array<bool, NUM_DIRS> entranceDirs;
      std::string name;
      static std::atomic<int> nodeCount;
  };
}
}
#endif
