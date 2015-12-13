#include <assert.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <stack>
#include <list>

#include "Savable.h"

using namespace boost;
using namespace boost::property_tree;
namespace fs = boost::filesystem;

namespace File {
  typedef ptree::value_type   pairType;
  typedef ptree               treeType;

  

  /** The folder in which saves will go. */
  const fs::path savePath("./Saves");
  fs::fstream file;
  fs::path filePath;
  treeType masterTree;
  std::stack<treeType*, std::list<treeType*>> treeStack;

  /* For storage of information. */
  treeType* workingTree() {
    treeType* treePtr = nullptr;
    if (treeStack.empty()) {
      treePtr = &masterTree;
    }
    else {
      treePtr = treeStack.top();
    }

    return treePtr; 
  }


Savable::Savable(): id(0)
{
}

Savable::~Savable()
{
}

void Savable::startSave(const std::string& key)
{
  // Make a new tree to add new vars to
  // Add the pair to the working tree
  workingTree()->push_back(pairType(key, ptree()));

  // Get pointer to tree just added
  auto lastPairIt = --workingTree()->end();
  treeType* subTreePtr = &lastPairIt->second;

  // Add pointer to stack for later use
  treeStack.push(subTreePtr);
  subTreePtr->data();
}

void Savable::endSave()
{
  assert(!treeStack.empty());
  treeStack.pop();
}

void Savable::addVariable(const std::string & varName, int var)
{
  addVariable(varName, std::to_string(var));
}

void Savable::addVariable(const std::string & varName, const std::string & var)
{
  pairType p{ varName, treeType(var) };
  workingTree()->push_back(p);
}

void Savable::readVariable(const std::string & varName, int & var)
{
  std::string stringValue;
  readVariable(varName, stringValue);

  // Convert value to int
  var = std::stoi(stringValue);
}

void Savable::readVariable(const std::string & varName, std::string & var)
{ // TODO: Implement this
  // Find var in tree

  // Get the data

  // assign value

  // Clear node in tree

}

} // namespace File
