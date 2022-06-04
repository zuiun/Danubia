#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include "game_object.hpp"

class Tile : GameObject {
public:
	Tile (std::string path);
	~Tile ();
private:
	unsigned char type;
};

#endif