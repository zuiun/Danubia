#pragma once
#ifndef CHARACTER_MANAGER_HPP
#define CHARACTER_MANAGER_HPP

#include "../objects/game/character.hpp"

class CharacterManager {
public:
	enum Actions {
		ATTACK,
		MAGIC,
		FORMATION,
		WEAPON,
		SKILL,
		WAIT,
		AI
	};

	CharacterManager ();
	unsigned int act (Actions const action, Character& character);
	void begin_turn (Character& character);
	void end_turn (Character& character);
	void modify_stat (Stats::Field const stat, int const amount, Character& character);
private:
	Character::delays_t delay_bases;

	void attack (Character& character, Character& target);
};

#endif
