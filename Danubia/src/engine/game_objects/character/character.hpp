#pragma once
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <array>
#include <iostream>
#include <vector>
#include "skill.hpp"
#include "../game_object.hpp"

class Character : GameObject {
public:
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
	};
	struct Stats {
		// 0 - 1000
		unsigned short health {1000};
		// 0 - 200
		unsigned char morale {100};
		// 0 - 100
		unsigned char attack {};
		// 0 - 100
		unsigned char defence {};
		// 0 - 100
		unsigned char magic {};
		// 0 - 100
		unsigned char speed {};
		// 0 - 200
		unsigned char cohesion {100};
	};
	struct Weapon {
		enum Weapons {
			FIREARM,
			MELEE,
			ARTILLERY,
			LENGTH
		};

		unsigned char attack {10};
		unsigned char slash {0};
		unsigned char pierce {0};
		unsigned char decay {0};
		unsigned char skill {0};
	};
	enum Actions {
		ATTACK,
		MAGIC,
		FORMATION,
		WEAPON,
		SKILL,
		WAIT,
		LENGTH
	};

	Character (std::string path, bool is_player);
	unsigned int act (Actions action);
	void damage (unsigned int health_damage, unsigned int morale_damage);
	void time_modifiers ();
	void expire_modifiers ();
	bool get_is_player ();
private:
	using delays_t = std::array<unsigned int, 100>;

	delays_t const delay_bases {};

	Stats stats {};
	std::vector<Skill> skills {};
	std::vector<Modifier> modifiers {};
	std::array<Weapon, Weapon::Weapons::LENGTH> weapons {};
	bool is_player {false};

	static delays_t calculate_delays ();
	void switch_weapons ();
	void attack (Character& target);
};

#endif
