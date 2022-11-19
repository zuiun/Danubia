#pragma once
#ifndef CHARACTER_MANAGER_HPP
#define CHARACTER_MANAGER_HPP

#include "../objects/game/unit.hpp"

class CharacterManager {
public:
	enum Actions {
		MOVE,
		ATTACK,
		MAGIC,
		FORMATION,
		WEAPON,
		SKILL,
		WAIT,
		AI
	};

	CharacterManager ();
	static Unit::delays_t calculate_delays ();
	unsigned int act (Actions const action, Unit& character);
	void begin_turn (Unit& character);
	void end_turn (Unit& character);
	void modify_stat (Stats::Field const stat, int const amount, Unit& character);
private:
	Unit::delays_t const DELAYS {};
	const float MAGIC_DELAY {1.4f};
	const float WAIT_DELAY {0.6f};

	void attack (Unit& character, Unit& target);
};

#endif
