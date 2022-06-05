#include "character.hpp"

Character::Character (std::string path, bool is_player) :
	GameObject {path},
	skills {},
	is_player {is_player} {
	// TODO: Import character from file, eventually
}

void Character::act () {

}

bool Character::get_is_player () {
	return is_player;
}
