#ifndef FILE_H
#define FILE_H
#include <string>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
/** Useful for outputing to xml. Makes output pretty and easy to read. */
#define XML_VAR_PAIR(c) ptree::value_type{#c, ptree{to_string(c)}}
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
