#include <assert.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
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
  ADD_VAR(id);
}

void Savable::endSave()
{
  assert(!treeStack.empty());
  treeStack.pop();
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
  std::string stringValue;
  load(varName, stringValue);

  // Convert value to int
  var = std::stoi(stringValue);
}

void Savable::load(const std::string & varName, std::string & var)
{ // TODO: Implement this
  // Find var in tree

  // Get the data

  // assign value

  // Clear node in tree

}

void save(const std::string & fileName)
{
  using namespace File;
  using namespace boost::property_tree;

  // Path to file
  fs::path filePath = savePath;
  filePath /= fs::path{ fileName }.filename();
  filePath += ".sav";

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
  filePath /= fs::path{fileName};
  filePath += ".sav";
  
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

} // namespace File
