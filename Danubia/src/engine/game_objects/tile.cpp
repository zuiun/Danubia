#include "tile.hpp"

Tile::Tile (std::string path) :
	GameObject (path) {
	this->type = 0;
}

Tile::~Tile () {

}
