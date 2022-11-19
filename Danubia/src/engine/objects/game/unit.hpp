#pragma once
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <array>
#include <string>
#include <vector>
#include "game_object.hpp"
#include "tile.hpp"

struct Skill {

};

struct Stats {
	enum Field {
		// 0 - 1000
		STRENGTH,
		// 0 - 200
		MORALE,
		// 0 - 100
		ATTACK,
		// 0 - 100
		DEFENCE,
		// 0 - 100
		MAGIC,
		// 0 - 100
		SPEED,
		// 0 - 200
		COHESION,
		LENGTH
	};

	using stats_t = std::array<unsigned int, Field::LENGTH>;
	stats_t const MAXIMUMS {1000, 200, 100, 100, 100, 100, 200};

	stats_t fields {1000, 100, {}, {}, {}, {}, 100};
};

struct Weapon {
	enum Types {
		PRIMARY,
		SECONDARY,
		LENGTH
	};

	unsigned char attack {10};
	unsigned char slash {0};
	unsigned char pierce {0};
	unsigned char decay {0};
	unsigned char skill {0};
};

enum Factions {
	NATIONAL_LEAGUE,
	KINGOM_ATRILIS,
	HOUSE_SZECHENYI,
	YOUNG_PONUMIA,
	KINGDOM_WILNOR,
	MARGRAVIATE_TRAES,
	REPUBLIC_TRAES,
	UNITED_DUCHY_RECIA_BERNE,
	DUCHY_BASEL,
	LUSATIAN_REVOLUTIONARY_ALLIANCE,
	PRINCIPALITY_COROND,
	KINGDOM_ANTERIA,
	LUSATIAN_REPUBLIC,
	CONFEDERATION_GYOR
};

enum Class {
	WORKER_MILITIA,
	PARAMILITARY,
	PEASANT_IRREGULAR,
	STUDENT_MILITIA,
	HUSSAR,
	LINE_INFANTRY,
	ARTILLERY,
	CUIRASSIER
};

struct Unit : GameObject {
	using delays_t = std::array<unsigned int, 100>;
	delays_t const delay_bases {};

	Stats current_stats {};
	std::vector<Skill> skills {};
	std::array<Weapon, Weapon::Types::LENGTH> weapons {};
	Factions faction {NATIONAL_LEAGUE};
	Tile tile;
};

struct Character {
	Stats current_stats {};
	Unit unit {};
	std::vector<Unit> subordinates {};
};

#endif
