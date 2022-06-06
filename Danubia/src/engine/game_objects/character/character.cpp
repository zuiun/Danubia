#include <cmath>
#include "character.hpp"

Character::Character (std::string path, bool is_player) :
	delay_bases {calculate_delays ()},
	GameObject {path},
	is_player {is_player} {
	// TODO: Import character from file, eventually
}

std::array<unsigned int, 100> Character::calculate_delays () {
	std::array<unsigned int, 100> result {};

	for (int i = 0; i < result.size (); i++) {
		result[i] = 1 + static_cast<unsigned int> (20 / exp (0.04 * i));
	}

	return result;
}

void Character::switch_weapons () {

}

void Character::attack (Character& target) {
	// Base damage
	Weapon weapon = weapons.front ();
	unsigned int damage {stats.attack > target.stats.defence ? stats.attack - target.stats.defence : static_cast<unsigned int> (1)};

	damage += weapon.decay * 2;
	target.damage (damage + (weapon.slash * 2), damage + (weapon.pierce * 2));
	// target.attack (*this);
}

void Character::damage (unsigned int health_damage, unsigned int morale_damage) {

}

/*
 * Performs character action
 * 
 * Pre:
 * Post:
 * Return: Turn delay
 */
unsigned int Character::act (Actions action) {
	// Turn-ending actions
	switch (action) {
		case ATTACK:
			return delay_bases[stats.speed];
			break;
		case MAGIC:
			return static_cast<unsigned int> (delay_bases[stats.speed] * 1.4);
			break;
		case FORMATION:
			break;
		case WEAPON:
			break;
		case SKILL:
			break;
		case WAIT:
			return static_cast<unsigned int> (delay_bases[stats.speed] * 0.6);
			break;
	}
	 /* * 0.6 + (0.4 * delay_modifier) */;
	// Condition-changing actions
	// Move, although the character only moves when the turn ends (allows other actions after moving, but prevents moving past original move area)
	// Weapon
	// Formation
	// Skill
	return 0;
}

bool Character::get_is_player () {
	return is_player;
}
