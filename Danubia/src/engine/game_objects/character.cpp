#include "character.hpp"

Character::Character (std::string path, bool is_player) :
	GameObject (path) {
	this->skills = new std::vector<Skill*> ();
	this->is_player = is_player;
}

Character::~Character () {

}

bool Character::get_is_player () {
	return is_player;
}
