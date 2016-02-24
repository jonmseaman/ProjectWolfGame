#include <assert.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <string>
#include <stack>
#include <list>

#include "Savable.h"

using namespace boost;
using namespace boost::property_tree;
namespace fs = boost::filesystem;

namespace File {

// Data for File::

  typedef ptree::value_type   pairType;
  typedef ptree               treeType;



  /** The folder in which saves will go. */
  const fs::path savePath("./Saves");
  fs::fstream file;
  fs::path filePath;
  treeType masterTree;
  std::stack<treeType*, std::list<treeType*>> treeStack;
  std::stack<ptree::iterator, std::list<ptree::iterator>> eraseStack;

  /* For storage of information. */
  treeType* workingTree() {
    treeType* treePtr = &masterTree;
    if (!treeStack.empty()) {
      treePtr = treeStack.top();
    }

    return treePtr;
  }

// Methods in File::

void save(const std::string & fileName)
{
  using namespace File;
  using namespace boost::property_tree;

  // Path to file
  fs::path filePath = savePath;
  filePath /= fs::path{ fileName }.filename();
  filePath += ".xml";

  if (file.is_open())
  {
    file.close();
  }

  // Make sure the directory exists
  if (!exists(savePath)) {
    fs::create_directory(savePath);
  }

  // Try to open and save the file
  try {
    file.open(filePath, std::fstream::out);

    // write to file, with formatting
    xml_writer_settings<std::string> settings(' ', 2);
    xml_parser::write_xml(file, masterTree, settings);
  }
  catch (std::exception &e) {
    // TODO: Better catch
    std::cerr << e.what() << std::endl;
  }

  masterTree.clear();
  file.close();
}

void load(const std::string& fileName)
{
  using namespace File;
  using namespace boost::property_tree;

  fs::path filePath = savePath;
  filePath /= fs::path{ fileName }.filename();
  filePath += ".xml";

  if (file.is_open()) { file.close(); }

  try {
    file.open( filePath, std::fstream::in );
    xml_parser::read_xml(file, masterTree, xml_parser::trim_whitespace);
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  file.close();
}

void close() {
  masterTree.clear();

  // Clear both stacks
  treeStack = std::stack<treeType*, std::list<treeType*>>();
  eraseStack = std::stack<ptree::iterator, std::list<ptree::iterator>>();
}

//////////////////////
// Methods for Savable
//////////////////////

Savable::Savable(): id(0)
{
}

Savable::~Savable()
{
}

Savable::idType Savable::nextID(const std::string& key) {
  // look in current working tree for pair with key @param key
  auto it = workingTree()->begin();
  bool foundVar = false;
  while (it != workingTree()->end() && !foundVar) {
    // If found var data
    foundVar = it->first == key;
    if (!foundVar) {
      it++;
    }
  }

  // tree should have a child with key "id", find the child
  auto &tree = it->second;
  // find it
  auto idIterator = tree.find("id"); // TODO: Remove hardcoding
  if (idIterator != tree.not_found()) {
    auto idData = idIterator->second.data();
    return std::stoi(idData); // Convet to idType
  } else {
    // throw an exception?
    // TODO: fix this
    return 0;
  }

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
  SAVE(id);
}

void Savable::endSave()
{
  assert(!treeStack.empty());
  // We no longer want to work with this tree, so remove from stack
  treeStack.pop();
}

void Savable::startLoad(const std::string & key)
{
  // look in current working tree for pair with key @param key
  auto it = workingTree()->begin();
  bool foundVar = false;
  while (it != workingTree()->end() && !foundVar) {
    // If found var data
    foundVar = it->first == key;
    if (!foundVar) {
      it++;
    }
  }

  // Add iterator to 'erase' stack so that it can be erased later
  eraseStack.push(it);

  // Add iterator's tree to tree stack so that we can load vars from it
  treeStack.push(&it->second);
}

void Savable::endLoad()
{
  // pop tree stack for loading
  treeStack.pop();
  // take iterator from 'erase' stack erase it from the working tree
  workingTree()->erase(eraseStack.top());
  // pop 'erase' stack
  eraseStack.pop();
}

void Savable::save(const std::string & varName, int var) const
{
  save(varName, std::to_string(var));
}

void Savable::save(const std::string & varName, const std::string & var) const
{
  pairType p{ varName, treeType(var) };
  workingTree()->push_back(p);
}

void Savable::load(const std::string & varName, int & var)
{
  std::string stringValue = "";
  load(varName, stringValue);

  // Convert value to int
  var = std::stoi(stringValue);
}

void Savable::load(const std::string & varName, std::string & var)
{
  // Find var in tree
  auto it = workingTree()->begin();

  bool foundVar = false;
  while (it != workingTree()->end() && !foundVar) {
    // If found var data
    foundVar = it->first == varName;
    if (!foundVar) {
      it++;
    }
  }

  if (it != workingTree()->end()) {
    // TODO: Throw an exception? if we are at end
    // Get and assign value
    var = it->second.data();
    // Clear node in tree
    workingTree()->erase(it);
  }
}

bool Savable::canLoad(const std::string &key)
{
  bool foundSavable = false;

  auto it = workingTree()->begin();
  while (!foundSavable && it != workingTree()->end())
  {
    foundSavable = it->first == key;
    if (!foundSavable)
    {
      it++;
    }
  }

  return foundSavable;
}

} // namespace File
