#if PWG_IMPORT_STD
import std;
#else
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <stack>
#include <list>
#include <vector>
#endif

// assert() is a macro, and macros never come from `import std`.
#include <assert.h>

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

// XML escaping
//
// Values come from the game (item names, descriptions, creature names), so
// they can contain characters that are markup in XML. They are escaped on the
// way out and put back on the way in. Newlines are escaped as well: the reader
// below is line based, so a raw newline inside a value would split it in two.

static std::string escapeXml(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        switch (c) {
            case '&':  out += "&amp;";  break;
            case '<':  out += "&lt;";   break;
            case '>':  out += "&gt;";   break;
            case '\n': out += "&#10;";  break;
            case '\r': out += "&#13;";  break;
            default:   out += c;        break;
        }
    }
    return out;
}

static std::string unescapeXml(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    // Single pass, so that an escaped entity such as "&amp;lt;" comes back as
    // the literal text "&lt;" instead of being unescaped a second time.
    for (std::size_t i = 0; i < s.size(); ) {
        if (s[i] != '&') { out += s[i++]; continue; }
        std::size_t semi = s.find(';', i);
        if (semi == std::string::npos) { out += s[i++]; continue; }
        std::string entity = s.substr(i, semi - i + 1);
        if      (entity == "&amp;")  { out += '&';  }
        else if (entity == "&lt;")   { out += '<';  }
        else if (entity == "&gt;")   { out += '>';  }
        else if (entity == "&quot;") { out += '"';  }
        else if (entity == "&apos;") { out += '\''; }
        else if (entity == "&#10;")  { out += '\n'; }
        else if (entity == "&#13;")  { out += '\r'; }
        else { out += s[i++]; continue; } // not an entity we know; keep as-is
        i = semi + 1;
    }
    return out;
}

// XML write helpers

static void writeXmlNode(std::ostream& out, const XmlNode& node,
                         const std::string& tag, int depth) {
    std::string ind(depth * 2, ' ');
    out << ind << "<" << tag << ">";
    if (node.children.empty()) {
        out << escapeXml(node.value);
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
                child.value = unescapeXml(t.substr(valStart, closePos - valStart));
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
                child.value = unescapeXml(t.substr(valStart, closePos - valStart));
            } else {
                readXmlNode(in, child);
            }
            node.children.push_back({tag, std::move(child)});
        }
    }
}

// Methods in File::

/**
 * Save names become file names, so they are restricted to characters that are
 * safe in a path and cannot escape the save directory.
 */
static void validateFileName(const std::string &fileName, const char* caller) {
  if (fileName.empty()) {
    throw std::invalid_argument(std::string(caller) + ": file name cannot be empty.");
  }
  for (unsigned char c : fileName) {
    if (!(std::isalnum(c) || c == '_')) {
      throw std::invalid_argument(std::string(caller) +
        ": file name can only contain alpha-numeric characters and '_'.");
    }
  }
}

static fs::path saveFilePath(const std::string &fileName) {
  fs::path path = savePath;
  path /= fs::path{ fileName }.filename();
  path += ".xml";
  return path;
}

void save(const std::string & fileName)
{
  using namespace File;

  validateFileName(fileName, "File::save");
  fs::path filePath = saveFilePath(fileName);

  if (file.is_open()) {
    file.close();
  }

  // Make sure the directory exists
  std::error_code ec;
  fs::create_directories(savePath, ec);
  if (ec) {
    throw SaveError("File::save: could not create save directory '"
      + savePath.string() + "': " + ec.message());
  }

  file.open(filePath, std::fstream::out | std::fstream::trunc);
  if (!file.is_open()) {
    // The stream has no exception mask, so a failed open has to be checked
    // for; wrapping it in try/catch never reported anything.
    throw SaveError("File::save: could not open '" + filePath.string()
      + "' for writing.");
  }

  // write to file, with formatting
  writeXml(file, masterTree);
  file.flush();
  const bool written = file.good();
  file.close();

  // The save has been consumed either way; do not leave a half written tree
  // behind for the next save to pick up.
  masterTree.clear();

  if (!written) {
    throw SaveError("File::save: failed while writing '" + filePath.string() + "'.");
  }
}

void load(const std::string& fileName)
{
  using namespace File;

  validateFileName(fileName, "File::load");
  fs::path filePath = saveFilePath(fileName);

  if (file.is_open()) { file.close(); }

  // Discard anything already in the tree. Without this, loading a file twice
  // leaves two copies of every entry in it, and a half finished save leaks
  // into the loaded data.
  clear();

  file.open( filePath, std::fstream::in );
  if (!file.is_open()) {
    throw SaveError("File::load: save file '" + filePath.string()
      + "' does not exist or could not be opened.");
  }

  readXml(file, masterTree);
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
  auto it = workingTree()->find(key);
  if (it == workingTree()->not_found()) {
    // Previously this walked off the end of the tree and dereferenced it,
    // which crashed on any save file that was missing, truncated, or simply
    // did not contain what the caller expected. (GitHub issue #20)
    throw SaveError("Savable::nextID: no '" + key
      + "' entry is available to load.");
  }

  // tree should have a child with key "id", find the child
  auto &tree = it->second;
  auto idIterator = tree.find("id"); // TODO: Remove hardcoding
  if (idIterator == tree.not_found()) {
    throw SaveError("Savable::nextID: the '" + key
      + "' entry being loaded has no 'id'.");
  }
  return idIterator->second.data();
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
  auto it = workingTree()->find(key);
  if (it == workingTree()->not_found()) {
    // Nothing is pushed onto either stack on this path, so the stacks stay
    // balanced and the caller's endLoad() is simply never reached.
    throw SaveError("Savable::startLoad: no '" + key
      + "' entry is available to load.");
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
  std::size_t charsUsed = 0;
  int parsed = 0;
  try {
    parsed = std::stoi(stringValue, &charsUsed);
  } catch (const std::exception &) {
    throw SaveError("Savable::load: '" + varName + "' is not a valid integer (saved as \""
      + stringValue + "\").");
  }
  if (charsUsed != stringValue.size()) {
    throw SaveError("Savable::load: '" + varName + "' is not a valid integer (saved as \""
      + stringValue + "\").");
  }
  var = parsed;
}

void Savable::load(const std::string & varName, std::string & var)
{
  // Find var in tree
  auto it = workingTree()->find(varName);
  if (it == workingTree()->not_found()) {
    // Leaving var untouched here hid truncated and mismatched save files,
    // and left the caller reading whatever the variable happened to hold.
    throw SaveError("Savable::load: no value was saved for '" + varName + "'.");
  }

  // Get and assign value
  var = it->second.data();
  // Clear node in tree
  workingTree()->erase(it);
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
