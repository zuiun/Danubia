#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "engine/controls_manager.hpp"
#include "engine/scene.hpp"

class Game {
public:
	// TODO: Consider using bool bit-fields or bit packing?
	struct Settings {
		bool unlimited_frame_rate;
		bool is_fullscreen;

		Settings () :
			unlimited_frame_rate (false),
			is_fullscreen (true) {
		}
	};

	Game (SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);
	void update ();
	bool get_is_running ();
private:
	// WAIT_TIMES[0] = 60 frames/second, WAIT_TIMES [1] = unlimited frames/second
	const unsigned int WAIT_TIMES[2] = {1000 / 60, 0};

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	Settings* settings;
	ControlsManager* controls_manager;
	std::vector <Scene*>* scenes;
	Scene* scene;
	bool is_running;

	void import_file (std::string path, std::function<void (SDL_RWops* file, bool is_found)> importer);
	void handle_event ();
	void import_sprite_sheets ();
	void import_tile_sprite_sheet ();
	void import_character_sprite_sheet ();
};

#endif
