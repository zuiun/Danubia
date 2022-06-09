#pragma once
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <array>
#include <iostream>
#include <vector>
#include "modifiers/skill.hpp"
#include "game_object.hpp"

class Character : GameObject {
public:
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
		AI
	};
	enum Factions {
		NATIONAL_LEAGUE,
		KINGOM_ATRILIS,
		HOUSE_SZECHENYI,
		YOUNG_PONUMIA,
		GYOR_CONFEDERATION,
		KINGDOM_WILNOR,
		MARGRAVIATE_TRAES,
		REPUBLIC_TRAES,
		UNITED_DUCHY_RECIA_BERNE,
		DUCHY_BASEL,
		LUSATIA_REVOLUTIONARY_ALLIANCE,
		PRINCIPALITY_COROND,
		KINGDOM_ANTERIA
	};

	Character (std::string path);
	unsigned int act (Actions action, Character& target);
	void damage (unsigned int health_damage, unsigned int morale_damage);
	void time_modifiers ();
	void expire_modifiers ();
	Factions get_faction ();
private:
	using delays_t = std::array<unsigned int, 100>;

	delays_t const delay_bases {};

	Stats stats {};
	std::vector<Skill> skills {};
	std::vector<Modifier> modifiers {};
	std::array<Weapon, Weapon::Weapons::LENGTH> weapons {};
	Factions faction {NATIONAL_LEAGUE};

	static delays_t calculate_delays ();
	void switch_weapon ();
	void attack (Character& target);
};

#endif
