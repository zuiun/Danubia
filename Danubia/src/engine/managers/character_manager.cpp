#include <algorithm>
#include <cmath>
#include "character_manager.hpp"

CharacterManager::CharacterManager () {
	for (int i = 0; i < delay_bases.size (); i++) {
		delay_bases[i] = 1 + static_cast<unsigned int> (20 / exp (0.04 * i));
	}
}

/*
 * Performs turn-beginning tasks
 */
void CharacterManager::begin_turn (Character& character) {
	// Remove expired modifiers
	std::erase_if (character.modifiers, [] (Modifier i) -> bool {
		return !i.time;
	});
}

/*
 * Performs turn-end tasks
 */
void CharacterManager::end_turn (Character& character) {
	// Decrease modifier turn counts
	for (Modifier i : character.modifiers) {
		if (i.time > 0) {
			i.time--;
		}
	}

	// Recover health and morale
	if (true /* not TODO: encircled */) {
		modify_stat (Stats::Field::HEALTH, 20, character);
	}
	
	modify_stat (Stats::Field::MORALE, 5, character);
}

void CharacterManager::modify_stat (Stats::Field const stat, int const amount, Character& character) {
	if (amount > 0) {
		character.stats.fields[stat] = std::min (character.stats.fields[stat] + amount, character.stats.MAXIMUMS[stat]);
	} else if (amount < 0) {
		character.stats.fields[stat] = std::max (character.stats.fields[stat] + amount, 0U);
	}
}

/*
 * Performs character action
 *
 * Pre:
 * Post:
 * Return: Turn delay
 */
unsigned int CharacterManager::act (Actions const action, Character& character) {
	switch (action) {
		case Actions::ATTACK:
			attack (character, character);
			return delay_bases[character.stats.fields[Stats::Field::SPEED]];
			break;
		case Actions::MAGIC:
			return static_cast<unsigned int> (delay_bases[character.stats.fields[Stats::Field::SPEED]] * 1.4);
			break;
		case Actions::FORMATION:
			break;
		case Actions::WEAPON:
			break;
		case Actions::SKILL:
			break;
		case Actions::WAIT:
			return static_cast<unsigned int> (delay_bases[character.stats.fields[Stats::Field::SPEED]] * 0.6);
			break;
		case Actions::AI:
			break;
	}

	return 0;
}

void CharacterManager::attack (Character& character, Character& target) {
	// Base damage
	Weapon weapon {character.weapons.front ()};
	unsigned int damage {(character.stats.fields[Stats::Field::ATTACK] + weapon.attack) > target.stats.fields[Stats::Field::DEFENCE] ? (character.stats.fields[Stats::Field::ATTACK] + weapon.attack) - target.stats.fields[Stats::Field::DEFENCE] : 1U};

	damage += weapon.decay * 2;
	modify_stat (Stats::Field::HEALTH, damage + (weapon.slash * 2), target);
	modify_stat (Stats::Field::MORALE, damage + (weapon.pierce * 2), target);
}
