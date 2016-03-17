#include <assert.h>
#include <string>
#include "Dir.h"

namespace Maps {

int charToDir(char dir) {
	int intDir = 0;
	if (dir == 'w') {
		intDir = Maps::North;
	}
	else if (dir == 'a') {
		intDir = Maps::West;
	}
	else if (dir == 's') {
		intDir = Maps::South;
	}
	else if (dir == 'd') {
		intDir = Maps::East;
	}
	else if (dir == 'q') {
		intDir = Maps::Down;
	}
	else if (dir == 'e') {
		intDir = Maps::Up;
	}
	return intDir;
}

std::string dirName(int dir) {
	assert(0 <= dir && dir < NUM_DIRS);

	std::string dirName;
	if (dir == Dir::Stop) {
		dirName = "Stop";
	} else if (dir == Dir::North) {
		dirName = "North";
	} else if (dir == Dir::East) {
		dirName = "East";
	} else if (dir == Dir::West) {
		dirName = "West";
	} else if (dir == Dir::South) {
		dirName = "South";
	} else if (dir == Dir::Up) {
		dirName = "Up";
	} else if (dir == Dir::Down) {
		dirName = "Down";
	}
	return dirName;
}

int oppositeDir(int dir) {
	assert(0 <= dir && dir < NUM_DIRS);

	int revDir; // The reverse directoin
	if (dir == Dir::Stop) {
		revDir = Dir::Stop;
	} else if (dir == Dir::North) {
		revDir = Dir::South;
	} else if (dir == Dir::East) {
		revDir = Dir::West;
	} else if (dir == Dir::West) {
		revDir = Dir::East;
	} else if (dir == Dir::South) {
		revDir = Dir::North;
	} else if (dir == Dir::Up) {
		revDir = Dir::Down;
	} else if (dir == Dir::Down) {
		revDir = Dir::Up;
	}
	return revDir;
}


} // End Maps
