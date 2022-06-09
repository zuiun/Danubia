#include <cmath>
#include "character.hpp"

Character::Character (std::string path) :
	delay_bases {calculate_delays ()},
	GameObject {path} {
	// TODO: Import character from file, eventually
}

Character::delays_t Character::calculate_delays () {
	delays_t result {};

	for (int i = 0; i < result.size (); i++) {
		result[i] = 1 + static_cast<unsigned int> (20 / exp (0.04 * i));
	}

	return result;
}

void Character::switch_weapon () {

}

void Character::attack (Character& target) {
	// Base damage
	Weapon weapon {weapons.front ()};
	unsigned int damage {(stats.attack + weapon.attack) > target.stats.defence ? (stats.attack + weapon.attack) - target.stats.defence : 1U};

	damage += weapon.decay * 2;
	target.damage (damage + (weapon.slash * 2), damage + (weapon.pierce * 2));
	// target.attack (*this);
}

void Character::damage (unsigned int health_damage, unsigned int morale_damage) {
	if (stats.health < health_damage) {
		// TODO: Die
	}

	if (stats.morale < morale_damage) {
		// TODO: Retreat
	}
}

/*
 * Decreases turn counter on modifiers
 * This takes place at the end of a turn
 */
void Character::time_modifiers () {
	for (Modifier i : modifiers) {
		if (i.time > 0) {
			i.time--;
		}
	}
}

/*
 * Removes expired modifiers
 * This takes place at the beginning of a turn
 */
void Character::expire_modifiers () {
	std::erase_if (modifiers, [] (Modifier i) -> bool {
		return i.time == 0;
	});
}

/*
 * Performs character action
 * 
 * Pre:
 * Post:
 * Return: Turn delay
 */
unsigned int Character::act (Actions action, Character& target) {
	switch (action) {
		case Actions::ATTACK:
			attack (target);
			return delay_bases[stats.speed];
			break;
		case Actions::MAGIC:
			return static_cast<unsigned int> (delay_bases[stats.speed] * 1.4);
			break;
		case Actions::FORMATION:
			break;
		case Actions::WEAPON:
			switch_weapon ();
			break;
		case Actions::SKILL:
			break;
		case Actions::WAIT:
			return static_cast<unsigned int> (delay_bases[stats.speed] * 0.6);
			break;
		case Actions::AI:
			break;
	}
	return 0;
}

Character::Factions Character::get_faction () {
	return faction;
}
