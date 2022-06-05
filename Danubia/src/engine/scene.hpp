#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "controls_manager.hpp"
#include "game_objects/character.hpp"
#include "game_objects/tile.hpp"
#include "ui/ui_manager.hpp"

class Scene {
public:
	Scene (const std::shared_ptr<SDL_Renderer> renderer, const unsigned int width, const unsigned int height);
	void render ();
	void update ();
private:
	const SDL_Colour BLACK = {0, 0, 0};

	std::shared_ptr<SDL_Renderer> renderer;
	std::shared_ptr<TTF_Font> font;
	ControlsManager controls_manager;
	UIManager ui_manager;
	std::vector<std::vector<Tile>> grid;
	unsigned int turn;
};

#endif
