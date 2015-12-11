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

  std::stack<pairType, std::list<pairType>> saveStack;

  /* For storage of information. */
  boost::property_tree::ptree masterTree;


Savable::Savable()
{
}

Savable::~Savable()
{
}

void Savable::start(std::string key)
{
  saveStack.push(pairType(key, ptree());
}

void Savable::end()
{
  pairType &p = saveStack.top();
  saveStack.pop();
  saveStack.top().second.push_back(p);
}

} // namespace File
