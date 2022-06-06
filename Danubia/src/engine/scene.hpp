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
#include "ui/ui_manager.hpp"

class Scene {
public:
	struct Turn {
		std::vector<Character> turn {};
	};

	Scene (std::shared_ptr<SDL_Renderer> const renderer);
	Scene (std::shared_ptr<SDL_Renderer> const renderer, unsigned int const width, unsigned int const height);
	void handle_event (SDL_Event const& event);
	void update ();
private:
	SDL_Colour const BLACK {0, 0, 0};

	std::shared_ptr<SDL_Renderer> renderer {};
	std::shared_ptr<TTF_Font> font {};
	ControlsManager controls_manager {};
	UIManager ui_manager {};
	std::vector<std::vector<Tile>> grid {};
	// 100 should be large enough for turn to loop around without collisions
	std::array<Turn, 100> turns {};
	unsigned int turn {0};

	void render ();
};

#endif
