#include <stdexcept>
#include <string>
#include "Dir.h"

namespace Engine {
namespace Maps {

using enum Dir;

Dir charToDir(char dir) {
	switch (dir) {
		case 'w': return NORTH;
		case 'a': return WEST;
		case 's': return SOUTH;
		case 'd': return EAST;
		case 'q': return DOWN;
		case 'e': return UP;
		default:  return STOP;
	}
}

std::string dirName(Dir dir) {
	switch (dir) {
		case STOP:  return "Stop";
		case NORTH: return "North";
		case EAST:  return "East";
		case WEST:  return "West";
		case SOUTH: return "South";
		case UP:    return "Up";
		case DOWN:  return "Down";
	}
	throw std::invalid_argument("dirName: unknown Dir value");
}

Dir oppositeDir(Dir dir) {
	switch (dir) {
		case STOP:  return STOP;
		case NORTH: return SOUTH;
		case EAST:  return WEST;
		case WEST:  return EAST;
		case SOUTH: return NORTH;
		case UP:    return DOWN;
		case DOWN:  return UP;
	}
	throw std::invalid_argument("oppositeDir: unknown Dir value");
}


} // End Maps
} // End Engine
