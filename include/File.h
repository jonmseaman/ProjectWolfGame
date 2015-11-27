#ifndef FILE_H
#define FILE_H
#include <string>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>

/** Useful for outputing to xml. Makes output pretty and easy to read. */
#define XML_VAR_PAIR(c) boost::property_tree::ptree::value_type{#c, boost::property_tree::ptree{std::to_string(c)}}
/** Same as XML_VAR_PAIR except for strings */
#define XML_VAR_SPAIR(s) boost::property_tree::ptree::value_type{#s, boost::property_tree::ptree(s)}

typedef boost::property_tree::ptree           		treeType;
typedef boost::property_tree::ptree::value_type 	pairType;
  
namespace fs = boost::filesystem;
namespace File
{
  /** The folder in which saves will go. */
  const fs::path savePath{"./Saves"};
  extern fs::fstream file;
  extern fs::path filePath;
  bool loadFile(const std::string &fName); // Opens ./savePath/fileName for load
  void close(); // closes file

}
#endif
