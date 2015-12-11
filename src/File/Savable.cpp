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

  std::stack<pairType*, std::list<pairType*>> saveStack;

  /* For storage of information. */
  treeType masterTree;
  treeType* workingTree = nullptr;


Savable::Savable()
{
}

Savable::~Savable()
{
}

void Savable::start(std::string key)
{
  saveStack.push(new pairType(key, ptree()));
  workingTree = &saveStack.top()->second;
}

void Savable::end()
{
  pairType* p = saveStack.top();
  saveStack.pop();
  saveStack.top()->second.push_back(*p);
  workingTree = nullptr;
}

void Savable::addVariable(const std::string & varName, int var)
{
  addVariable(varName, std::to_string(var));
}

void Savable::addVariable(const std::string & varName, const std::string & var)
{
  pairType p{ varName, treeType(var) };
  workingTree->push_back(p);
}

void Savable::readVariable(const std::string & varName, int & var)
{
  std::string stringValue;
  readVariable(varName, stringValue);

  // Convert value to int
  var = std::stoi(stringValue);
}

void Savable::readVariable(const std::string & varName, std::string & var)
{
  // Find var in tree

  // Get the data

  // assign value

  // Clear node in tree

}

} // namespace File
