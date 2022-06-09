#pragma once
#ifndef MODIFIER_HPP
#define MODIFIER_HPP

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
	int time {};
	// Percentage change of modifier
	float amount {};
};

#endif
