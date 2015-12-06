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

  /** The folder in which saves will go. */
  const fs::path savePath("./Saves");
  fs::fstream file;
  fs::path filePath;

  std::stack<ptree::iterator, std::list<ptree::iterator>> saveTrees;

  /* For storage of information. */
  boost::property_tree::ptree* saveTree;
  

Savable::Savable()
{
  initSaveTree();
}

Savable::~Savable()
{
  clearSaveTree();
}

void Savable::clearSaveTree()
{
  delete saveTree;
  saveTree = nullptr;
}

void Savable::initSaveTree()
{
  saveTree = new ptree;
}

void Savable::addSavable(Savable & s)
{
}

void Savable::addVariableToTree(std::string varName, int var)
{
}

void Savable::addVariableToTree(std::string varName, std::string var)
{
}

void Savable::resetSaveTree()
{
}

void Savable::saveMasterTree(std::string fileName)
{
}

} // namespace File
