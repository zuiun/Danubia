#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include "game_object.hpp"

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

struct Tile : GameObject {
	Terrain type {GRASSLAND};
};

#endif
