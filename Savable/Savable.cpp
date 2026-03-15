#include <assert.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stack>
#include <list>

#include "Savable.h"

namespace fs = std::filesystem;

namespace File {

// XmlNode: drop-in replacement for boost::property_tree::ptree
struct XmlNode {
    std::string value;
    std::vector<std::pair<std::string, XmlNode>> children;

    using value_type = std::pair<std::string, XmlNode>;
    using iterator   = std::vector<value_type>::iterator;

    XmlNode() = default;
    explicit XmlNode(std::string v) : value(std::move(v)) {}

    void     push_back(value_type p)    { children.push_back(std::move(p)); }
    iterator begin()                    { return children.begin(); }
    iterator end()                      { return children.end(); }
    iterator find(const std::string& k) {
        return std::find_if(children.begin(), children.end(),
                            [&](const value_type& p){ return p.first == k; });
    }
    iterator not_found()                { return children.end(); }
    std::string data() const            { return value; }
    void     erase(iterator it)         { children.erase(it); }
    void     clear()                    { children.clear(); value.clear(); }
};

// Data for File::

  typedef XmlNode::value_type   pairType;
  typedef XmlNode               treeType;

  /** The folder in which saves will go. */
  const fs::path savePath("./Saves");
  std::fstream file;
  fs::path filePath;
  treeType masterTree;
  std::stack<treeType*, std::list<treeType*>> treeStack;
  std::stack<XmlNode::iterator, std::list<XmlNode::iterator>> eraseStack;

  /* For storage of information. */
  treeType* workingTree() {
    treeType* treePtr = &masterTree;
    if (!treeStack.empty()) {
      treePtr = treeStack.top();
    }

    return treePtr;
  }

// XML write helpers

static void writeXmlNode(std::ostream& out, const XmlNode& node,
                         const std::string& tag, int depth) {
    std::string ind(depth * 2, ' ');
    out << ind << "<" << tag << ">";
    if (node.children.empty()) {
        out << node.value;
    } else {
        out << "\n";
        for (auto& [k, v] : node.children)
            writeXmlNode(out, v, k, depth + 1);
        out << ind;
    }
    out << "</" << tag << ">\n";
}

static void writeXml(std::ostream& out, const XmlNode& tree) {
    out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    for (auto& [k, v] : tree.children)
        writeXmlNode(out, v, k, 0);
}

// XML read helpers

static std::string trimWs(const std::string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    return s.substr(b, s.find_last_not_of(" \t\r\n") - b + 1);
}

static void readXmlNode(std::istream& in, XmlNode& node);

static void readXml(std::istream& in, XmlNode& root) {
    std::string line;
    while (std::getline(in, line)) {
        std::string t = trimWs(line);
        if (t.empty() || t.rfind("<?", 0) == 0) continue;
        if (t[0] == '<' && t[1] != '/') {
            size_t end = t.find_first_of("> \t");
            std::string tag = t.substr(1, end - 1);
            XmlNode child;
            std::string closeTag = "</" + tag + ">";
            size_t closePos = t.find(closeTag);
            if (closePos != std::string::npos) {
                size_t valStart = t.find('>') + 1;
                child.value = t.substr(valStart, closePos - valStart);
            } else {
                readXmlNode(in, child);
            }
            root.children.push_back({tag, std::move(child)});
        }
    }
}

static void readXmlNode(std::istream& in, XmlNode& node) {
    std::string line;
    while (std::getline(in, line)) {
        std::string t = trimWs(line);
        if (t.empty()) continue;
        if (t[0] == '<' && t[1] == '/') break; // closing tag
        if (t[0] == '<') {
            size_t end = t.find_first_of("> \t");
            std::string tag = t.substr(1, end - 1);
            XmlNode child;
            std::string closeTag = "</" + tag + ">";
            size_t closePos = t.find(closeTag);
            if (closePos != std::string::npos) {
                size_t valStart = t.find('>') + 1;
                child.value = t.substr(valStart, closePos - valStart);
            } else {
                readXmlNode(in, child);
            }
            node.children.push_back({tag, std::move(child)});
        }
    }
}

// Methods in File::

void save(const std::string & fileName)
{
  using namespace File;

  for (size_t i = 0; i < fileName.length(); i++) {
    char c = fileName.at(i);
    if (!(isalnum(c) || c == '_')){
      throw std::invalid_argument("File name can only contain alpha-numeric characters.");
    }
  }

  // Path to file
  fs::path filePath = savePath;
  filePath /= fs::path{ fileName }.filename();
  filePath += ".xml";

  if (file.is_open()) {
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
    writeXml(file, masterTree);
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

  fs::path filePath = savePath;
  filePath /= fs::path{ fileName }.filename();
  filePath += ".xml";

  if (file.is_open()) { file.close(); }

  try {
    file.open( filePath, std::fstream::in );
    readXml(file, masterTree);
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  file.close();
}

void clear() {
  masterTree.clear();

  // Clear both stacks
  treeStack = std::stack<treeType*, std::list<treeType*>>();
  eraseStack = std::stack<XmlNode::iterator, std::list<XmlNode::iterator>>();
}

//////////////////////
// Methods for Savable
//////////////////////

Savable::Savable() {}

Savable::~Savable() {}

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
    return idData;
  } else {
    // throw an exception?
    // TODO: fix this
    return "";
  }

}

void Savable::startSave(const std::string& key)
{
  // Make a new tree to add new vars to
  // Add the pair to the working tree
  workingTree()->push_back(pairType(key, XmlNode()));

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

void Savable::save(const std::string & varName, const char* var) const {
  save(varName, std::string(var));
}

void Savable::save(const std::string & varName, const std::string & var) const
{
  pairType p{ varName, XmlNode(var) };
  workingTree()->push_back(p);
}

void Savable::load(const std::string & varName, int & var)
{
  std::string stringValue = "";
  load(varName, stringValue);

  // Convert value to int
  var = std::stoi(stringValue);
}

void Savable::load(const std::string &varName, char* &var) {
  std::string stringValue;
  load(varName, stringValue);
  //var = stringValue.dat
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

void Savable::clearSavable() {}

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
