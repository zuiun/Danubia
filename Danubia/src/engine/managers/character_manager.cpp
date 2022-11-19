#include <algorithm>
#include <cmath>
#include "character_manager.hpp"

CharacterManager::CharacterManager () :
	DELAYS {calculate_delays ()} {
}

/*
 * Calculates delay table
 * Unit speed is an index into the table
 * Regular: 21 delay at 0, 20 delay at 1, 2 delay at 77, and 1 delay at 100
 * Magic: 29 delay at 0, 28 delay at 1, 3 delay at 77, and 1 delay at 100
 * Wait: 13 delay at 0, 12 delay at 1, 2 delay at 54, and 1 delay at 77
 *
 * Pre: None
 * Post: None
 * Return: Delay table
 */
Unit::delays_t CharacterManager::calculate_delays () {
	Unit::delays_t delays {};

	for (int i = 0; i < delays.size (); i++) {
		delays[i] = 1 + static_cast<unsigned int> (20 / exp (0.03 * i));
	}

	return delays;
}

/*
 * Performs turn-beginning tasks
 */
void CharacterManager::begin_turn (Unit& character) {
	// Remove expired modifiers
	std::erase_if (character.modifiers, [] (Modifier i) -> bool {
		return ! i.time;
	});
}

/*
 * Performs turn-end tasks
 */
void CharacterManager::end_turn (Unit& character) {
	// Decrease modifier turn counts
	for (Modifier i : character.modifiers) {
		if (i.time > 0) {
			i.time--;
		}
	}

	// Recover health and morale
	if (true /* TODO: not encircled */) {
		modify_stat (Stats::Field::STRENGTH, 20, character);
		modify_stat (Stats::Field::MORALE, 5, character);
	} else {
		modify_stat (Stats::Field::STRENGTH, -10, character);
		modify_stat (Stats::Field::MORALE, -5, character);
	}
}

void CharacterManager::modify_stat (Stats::Field const stat, int const amount, Unit& character) {
	if (amount > 0) {
		character.current_stats.fields[stat] = std::min (character.current_stats.fields[stat] + amount, character.current_stats.MAXIMUMS[stat]);
	} else if (amount < 0) {
		character.current_stats.fields[stat] = std::max (character.current_stats.fields[stat] + amount, 0U);
	}
}

/*
 * Performs character action
 *
 * Pre:
 * Post:
 * Return: Turn delay
 */
unsigned int CharacterManager::act (Actions const action, Unit& character) {
	switch (action) {
		case Actions::MOVE:
			break;
		case Actions::ATTACK:
			attack (character, character);
			return DELAYS[character.current_stats.fields[Stats::Field::SPEED]];
			break;
		case Actions::MAGIC:
			return static_cast<unsigned int> (round (DELAYS[character.current_stats.fields[Stats::Field::SPEED]] * MAGIC_DELAY));
			break;
		case Actions::FORMATION:
			break;
		case Actions::WEAPON:
			break;
		case Actions::SKILL:
			break;
		case Actions::WAIT:
			return static_cast<unsigned int> (round (DELAYS[character.current_stats.fields[Stats::Field::SPEED]] * WAIT_DELAY));
			break;
		case Actions::AI:
			break;
	}

	return 0;
}

void CharacterManager::attack (Unit& character, Unit& target) {
	// Base damage
	Weapon weapon {character.weapons.front ()};
	unsigned int damage {std::max ((character.current_stats.fields[Stats::Field::ATTACK] + weapon.attack) - target.current_stats.fields[Stats::Field::DEFENCE], 1U)};

	damage += weapon.decay * 2;
	modify_stat (Stats::Field::STRENGTH, damage + (weapon.slash * 2), target);
	modify_stat (Stats::Field::MORALE, damage + (weapon.pierce * 2), target);
}
