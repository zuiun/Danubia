#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <array>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "objects/character.hpp"
#include "objects/tile.hpp"
#include "managers/controls_manager.hpp"
#include "managers/media_manager.hpp"
#include "managers/ui_manager.hpp"
#include "../lists/scene_list.hpp"

class Scene {
public:
	Scene (std::shared_ptr<SDL_Renderer> const renderer, std::shared_ptr<TTF_Font> const font, scene_objects::Scenes const scene);
	void handle_event (SDL_Event const& event);
	void update ();
private:
	scene_objects::SceneData::Type const type {scene_objects::SceneData::Type::GAMEPLAY};

	ControlsManager controls_manager {};
	MediaManager media_manager {{}, {}};
	UIManager ui_manager {};
	std::vector<std::vector<Tile>> map {};
	// 100 should be large enough for turn to loop without collisions
	std::array<std::vector<Character>, 100> turns {};
	// Current turn
	unsigned int turn {0};
	// Total character actions
	unsigned int true_turns {0};
	// Total player actions
	unsigned int player_turns {0};
};

#endif
