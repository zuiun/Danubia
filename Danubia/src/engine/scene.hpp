#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <queue>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "objects/game/unit.hpp"
#include "objects/game/tile.hpp"
#include "managers/character_manager.hpp"
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
	// 100 should be large enough to loop without collisions
	static int const TURNS {100};
	scene_objects::SceneData::Type const TYPE {scene_objects::SceneData::Type::GAMEPLAY};

	CharacterManager character_manager {};
	ControlsManager controls_manager {};
	MediaManager media_manager;
	UIManager ui_manager {};
	std::vector<std::vector<Tile>> map {};
	std::array <std::queue<Unit>, TURNS> turns {};
	Factions player_faction {Factions::NATIONAL_LEAGUE};
	// Current turn
	unsigned int turn {0};
	// Total character actions
	unsigned int true_turns {0};
	// Total player actions
	unsigned int player_turns {0};
};

#endif
