#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include "game_object.hpp"
#include "modifiers/modifier.hpp"

class Tile : GameObject {
public:
	enum Terrain {
		GRASSLAND,
		HIGHLAND,
		MOUNTAIN,
		FOREST,
		MARSH,
		STEPPE,
		VOID,
		RIVER,
		WATER
	};

	Tile (std::string path);
private:
	Terrain type {GRASSLAND};
};

#endif
