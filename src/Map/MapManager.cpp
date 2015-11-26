#include <assert.h>
#include "MapManager.h"
#include "utils.h"
#include "Factory.h"
#include "File.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

MapManager::MapManager(): map(nullptr) {}

void MapManager::closeMap() {
  delete map;
  map = nullptr;
}

void MapManager::openMap(int mapNum) {
  using namespace Maps;
  Map* loadMap = Factory::newMap(mapNum);
  setMap( loadMap );
}

void openMap(std::string mapName) {
  //TODO: Implement this.
  // Should load a map from xml
}

void MapManager::setMap(Maps::Map* map) {
  if (this->map != nullptr) {
    delete map;
  }
  this->map = map;
}

void MapManager::play() {
  assert( map != nullptr );
  while ( true ) // TODO: Make variable for this
  {
    map->activate();
  }
}

void MapManager::save(std::string fileName) {
  assert(map != nullptr);
  using namespace File;
  using namespace boost::property_tree;

  fs::path filePath = savePath;
  filePath /= fs::path{fileName}.filename();
  if ( file.is_open() ) { file.close(); }
  if ( !exists( savePath )) {
    fs::create_directory(savePath);
  }
  file.open( filePath, std::fstream::out );

  // Make a tree
  ptree saveTree;
  // Add map to the tree
  saveTree.push_back(map->toXML());

  // write to file, with formatting
  xml_writer_settings<std::string> settings(' ', 2);
	xml_parser::write_xml(file, saveTree, settings);


  file.close();
}
