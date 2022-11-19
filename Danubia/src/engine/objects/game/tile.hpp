#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include <array>
#include <vector>
#include "game_object.hpp"

struct Terrain {
	enum Type {
		PLAIN,
		HILL,
		MOUNTAIN,
		FOREST,
		MARSH,
		VOID,
		RIVER,
		WATER,
		BRIDGE,
		ROAD,
		CITY,
		TOWN,
		LENGTH
	};

	// Can only take defence, speed, cohesion, and movement
	std::array<std::vector<Modifier>, Type::LENGTH> const TERRAIN_MODIFIERS {{{}, // Plain
																			 {{Modifier::Field::DEFENCE, {}, 0.3f}, {Modifier::Field::MOVEMENT, {}, -0.2f}}, // Hill
																			 {{Modifier::Field::DEFENCE, {}, 0.5f}, {Modifier::Field::COHESION, {}, -0.3f}, {Modifier::Field::MOVEMENT, {}, -0.4f}}, // Mountain
																			 {{Modifier::Field::DEFENCE, {}, 0.1f}, {Modifier::Field::COHESION, {}, -0.1f}, {Modifier::Field::MOVEMENT, {}, -0.1f}}, // Forest
																			 {{Modifier::Field::SPEED, {}, -0.3f}, {Modifier::Field::COHESION, {}, -0.4f}, {Modifier::Field::MOVEMENT, {}, -0.2f}}, // Marsh
																			 {{Modifier::Field::MOVEMENT, {}, -1.f}}, // Void
																			 {{Modifier::Field::DEFENCE, {}, -0.6f}, {Modifier::Field::MOVEMENT, {}, -0.5f}}, // River
																			 {{Modifier::Field::MOVEMENT, {}, -1.f}}, // Water
																			 {{Modifier::Field::MOVEMENT, {}, 0.1f}}, // Bridge
																			 {{Modifier::Field::MOVEMENT, {}, 0.1f}}, // Road
																			 {{Modifier::Field::DEFENCE, {}, 0.2f}, {Modifier::Field::COHESION, {}, -0.2f}}, // City
																			 {{Modifier::Field::DEFENCE, {}, 0.1f}}}}; // Town

	Type type {Type::PLAIN};
	std::vector<Modifier> modifiers {};
};

struct Tile : GameObject {
	Terrain terrain {};
	unsigned int row;
	unsigned int column;
};

#endif
