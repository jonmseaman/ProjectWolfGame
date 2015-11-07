#include "File.h"
#include "string"
#include <iostream>
// TODO: Temp file support
namespace File {
  fs::fstream file;
  fs::path filePath;
  bool saveFile( const std::string &fName )
  {
    fs::path filePath = savePath;
    filePath /= fs::path{fName}.filename();
    if ( file.is_open() ) { file.close(); }
    if ( !exists( savePath ))
    {
      fs::create_directory(savePath);
    }

    file.open( filePath, std::fstream::out );
	return file.is_open();
  }

  bool loadFile( const std::string &fName)
  {
    fs::path filePath = savePath;
    filePath /= fName;
    if ( file.is_open() ) { file.close(); }
    file.open( filePath, std::fstream::in );
	return file.is_open();
  }

  void close()
  {
    if ( file.is_open() ) { file.close(); }
  }
}
