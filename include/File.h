#ifndef FILE_H
#define FILE_H
#include <string>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
namespace File
{
  /**
   * The folder in which saves will go.
   */
  const fs::path savePath{"./Saves"};
  extern fs::fstream file;
  extern fs::path filePath;
  bool saveFile(const std::string &fName); // Opens ./savePath/fileName for save
  bool loadFile(const std::string &fName); // Opens ./savePath/fileName for load
  void close(); // closes file
}
#endif
