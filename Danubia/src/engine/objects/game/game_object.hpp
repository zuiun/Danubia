#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>
#include "../object.hpp"

struct Modifier {
	enum Types {
		MORALE,
		ATTACK,
		DEFENCE,
		MAGIC,
		SPEED,
		COHESION,
		SLASH,
		PIERCE,
		DECAY
	};

	// -1 = permanent, 0 or greater = timed
	int time {-1};
	// Percentage change of modifier
	float amount {};
};

struct GameObject : Object {
	std::vector<Modifier> modifiers {};
};

#endif
