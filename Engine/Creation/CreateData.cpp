module;

module Engine;

import std;

std::map<std::string, CreateData::ItemFactory> &CreateData::items() {
    static std::map<std::string, ItemFactory> factories;
    return factories;
}

std::map<std::string, CreateData::ActorFactory> &CreateData::actors() {
    static std::map<std::string, ActorFactory> factories;
    return factories;
}

std::map<std::string, CreateData::NodeFactory> &CreateData::nodes() {
    static std::map<std::string, NodeFactory> factories;
    return factories;
}

std::map<std::string, CreateData::MapFactory> &CreateData::maps() {
    static std::map<std::string, MapFactory> factories;
    return factories;
}
