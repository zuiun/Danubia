#include "tile.hpp"

Tile::Tile (std::string path) :
	GameObject {path},
	type {} {
	// TODO: Tiles could maybe be straight up hard-coded? But files are always a cool thing
}
