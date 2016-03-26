#include "CreateData.h"

CreateData createData;

std::map<std::string, Engine::Entity::Item* (*)()> CreateData::items;
std::map<std::string, Engine::Entity::Actor*> CreateData::actors;
std::map<std::string, Engine::Maps::Node* (*)()> CreateData::nodes;
std::map<std::string, Engine::Maps::Map* (*)()> CreateData::maps;
