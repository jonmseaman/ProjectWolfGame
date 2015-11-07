#include "NodeData.h"
#include <iostream>
#include <iomanip>
#include "utils.h"
#include "dLog.h"
namespace Maps
{
  NodeData::NodeData(): canMoveInDir{0,0,0,0,0,0,0}
    , arrMoveText{"", "","","","","",""}
    , moveLinks{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
  {
    dLog << "Maps::NodeData::NodeData() called" << std::endl;
    arrMoveText[Dir::Stop]="You may never leave...";
  }

  void NodeData::showData()
  {
    bool noDirs{true};
    if ( canMoveInDir[Dir::North] )
    {
      std::cout << std::setw(3) << std::right << Dir::North << ": " << "North to " << arrMoveText[Dir::North] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::East] )
    {
      std::cout << std::setw(3) << std::right << Dir::East << ": " << "East to " << arrMoveText[Dir::East] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::West] )
    {
      std::cout << std::setw(3) << std::right << Dir::West << ": " << "West to " << arrMoveText[Dir::West] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::South] )
    {
      std::cout << std::setw(3) << std::right << Dir::South << ": " << "South to " << arrMoveText[Dir::South] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::Up] )
    {
      std::cout << std::setw(3) << std::right << Dir::Up << ": " << "Up to " << arrMoveText[Dir::Up] << std::endl;
      noDirs = false;
    }
    if ( canMoveInDir[Dir::Down] )
    {
      std::cout << std::setw(3) << std::right << Dir::Down << ": " << "Down to " << arrMoveText[Dir::Down] << std::endl;
      noDirs = false;
    }
    if ( noDirs == true )
    {
      std::cout << arrMoveText[Dir::Stop] << std::endl;
    }
  } // End showData()

  void NodeData::setMoveData(int dir, const std::string &text, NodeData* link)
  {
    this->arrMoveText[dir] = text;
    this->moveLinks[dir] = link;
    if (text != "")
    {
      this->canMoveInDir[dir] = true;
    }
  }

  void NodeData::showActors()
  { // TODO: Is there a better way to interface with nodes?
  }

  Creature* NodeData::getActorPtr(int index)
  {
    return nullptr;
  }

  void NodeData::giveTarget(Creature* creature)
  {
    creature->setTarget(nullptr);
  }

  Inventory* NodeData::getInventory()
  {
    return nullptr;
  }

}
