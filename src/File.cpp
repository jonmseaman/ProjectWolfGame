#include "File.h"
#include "string"
#include <iostream>
// TODO: Temp file support
namespace File {
  fs::fstream file;
  fs::path filePath;

  bool loadFile( const std::string &fName) {
    fs::path filePath = savePath;
    filePath /= fName;
    if ( file.is_open() ) { file.close(); }
    file.open( filePath, std::fstream::in );
	return file.is_open();
  }

  void close() {
    if ( file.is_open() ) { file.close(); }
  }
}
