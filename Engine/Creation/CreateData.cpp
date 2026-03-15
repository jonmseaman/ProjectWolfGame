#include "CreateData.h"

std::map<std::string, std::function<std::unique_ptr<Engine::Entity::Item>()>>  CreateData::items;
std::map<std::string, std::function<std::unique_ptr<Engine::Entity::Actor>()>> CreateData::actors;
std::map<std::string, std::function<std::unique_ptr<Engine::Maps::Node>()>>    CreateData::nodes;
std::map<std::string, std::function<std::unique_ptr<Engine::Maps::Map>()>>     CreateData::maps;
