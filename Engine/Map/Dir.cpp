#include <assert.h>
#include <string>
#include "Dir.h"

namespace Engine {
namespace Maps {

int charToDir(char dir) {
	int intDir = 0;
	if (dir == 'w') {
		intDir = Maps::NORTH;
	}
	else if (dir == 'a') {
		intDir = Maps::WEST;
	}
	else if (dir == 's') {
		intDir = Maps::SOUTH;
	}
	else if (dir == 'd') {
		intDir = Maps::EAST;
	}
	else if (dir == 'q') {
		intDir = Maps::DOWN;
	}
	else if (dir == 'e') {
		intDir = Maps::UP;
	}
	return intDir;
}

std::string dirName(int dir) {
	assert(0 <= dir && dir < NUM_DIRS);

	std::string dirName;
	if (dir == Dir::STOP) {
		dirName = "Stop";
	} else if (dir == Dir::NORTH) {
		dirName = "North";
	} else if (dir == Dir::EAST) {
		dirName = "East";
	} else if (dir == Dir::WEST) {
		dirName = "West";
	} else if (dir == Dir::SOUTH) {
		dirName = "South";
	} else if (dir == Dir::UP) {
		dirName = "Up";
	} else if (dir == Dir::DOWN) {
		dirName = "DOWN";
	}
	return dirName;
}

int oppositeDir(int dir) {
	assert(0 <= dir && dir < NUM_DIRS);

	int revDir; // The reverse directoin
	if (dir == Dir::STOP) {
		revDir = Dir::STOP;
	} else if (dir == Dir::NORTH) {
		revDir = Dir::SOUTH;
	} else if (dir == Dir::EAST) {
		revDir = Dir::WEST;
	} else if (dir == Dir::WEST) {
		revDir = Dir::EAST;
	} else if (dir == Dir::SOUTH) {
		revDir = Dir::NORTH;
	} else if (dir == Dir::UP) {
		revDir = Dir::DOWN;
	} else if (dir == Dir::DOWN) {
		revDir = Dir::UP;
	}
	return revDir;
}


} // End Maps
} // End Engine
