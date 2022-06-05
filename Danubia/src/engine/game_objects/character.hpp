#pragma once
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <vector>
#include "effects/skill.hpp"
#include "game_object.hpp"

class Character : GameObject {
public:
	Character (std::string path, bool is_player);
	bool get_is_player ();
private:
	std::vector<Skill> skills;
	bool is_player;

	void act ();
};

#endif
