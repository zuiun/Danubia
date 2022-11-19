#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <string>
#include <vector>
#include "../object.hpp"

struct Modifier {
	enum Field {
		MORALE,
		ATTACK,
		DEFENCE,
		MAGIC,
		SPEED,
		COHESION,
		SLASH,
		PIERCE,
		DECAY,
		MOVEMENT
	};

	Field type {};
	// -1 = permanent, 0 or greater = timed
	int time {-1};
	// Percentage change of modifier
	float amount {};
};

struct GameObject : Object {
	std::string name {};
	std::vector<Modifier> modifiers {};
};

#endif
