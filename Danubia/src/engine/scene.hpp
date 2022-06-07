#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <array>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "controls_manager.hpp"
#include "game_objects/character/character.hpp"
#include "game_objects/tile.hpp"
#include "ui_manager.hpp"

class Scene {
public:
	enum Type {
		MENU,
		GAMEPLAY
	};

	Scene (std::shared_ptr<SDL_Renderer> const renderer, unsigned int const scene);
	void handle_event (SDL_Event const& event);
	void update ();
private:
	SDL_Colour const BLACK {0, 0, 0};
	Type const type {GAMEPLAY};

	std::shared_ptr<SDL_Renderer> renderer {};
	std::shared_ptr<TTF_Font> font {};
	ControlsManager controls_manager {};
	UIManager ui_manager {};
	std::vector<std::vector<Tile>> grid {};
	// 100 should be large enough for turn to loop around without collisions
	std::array<std::vector<Character>, 100> turns {};
	// Current turn
	unsigned int turn {0};
	// Total character actions
	unsigned int true_turns {0};
	// Total player actions
	unsigned int player_turns {0};

	void render ();
};

#endif
