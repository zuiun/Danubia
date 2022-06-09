#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "engine/managers/controls_manager.hpp"
#include "engine/scene.hpp"
#include "lists/scene_list.hpp"

class Game {
public:
	struct Settings {
		enum Masks {
			UNLIMITED_FRAME_RATE = 0b1,
			FULLSCREEN = 0b10,
		};

		bool is_unlimited_frame_rate {false};
		bool is_fullscreen {false};
	};

	Game (std::shared_ptr<SDL_Window> const window, std::shared_ptr<SDL_Renderer> const renderer, std::shared_ptr<TTF_Font> const font);
	void update ();
	bool get_is_running ();
private:
	std::array<unsigned int, 2> const WAIT_TIMES {1000 / 60, 0};
	std::string const SETTINGS_PATH {"saves/settings.bin"};

	std::shared_ptr<SDL_Window> window {};
	std::shared_ptr<SDL_Renderer> renderer {};
	std::shared_ptr<TTF_Font> font {};
	Settings settings {};
	Scene scene {renderer, font, scene_objects::Scenes::MENU};
	bool is_running {true};

	void import_file (std::string const& path, std::function<void (SDL_RWops* file, bool is_found)> const& importer);
	void handle_event ();
};

#endif
