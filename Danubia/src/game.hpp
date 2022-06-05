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
	struct Settings {
		enum {
			UNLIMITED_FRAME_RATE = 0b1,
			FULLSCREEN = 0b10,
		};

		unsigned char packed_settings;
		bool is_unlimited_frame_rate;
		bool is_fullscreen;

		Settings () :
			packed_settings {},
			is_unlimited_frame_rate {false},
			is_fullscreen {false} {
		}
		void unpack_settings (unsigned char raw_settings) {
			packed_settings = raw_settings;
			is_unlimited_frame_rate = raw_settings & UNLIMITED_FRAME_RATE;
			is_fullscreen = raw_settings & FULLSCREEN;
		}
		void pack_settings () {
			if (is_unlimited_frame_rate) {
				packed_settings |= UNLIMITED_FRAME_RATE;
			}

			if (is_fullscreen) {
				packed_settings |= FULLSCREEN;
			}
		}
	};

	Game (const std::shared_ptr<SDL_Window> window, const std::shared_ptr<SDL_Renderer> renderer, const std::shared_ptr<TTF_Font> font);
	void update ();
	bool get_is_running ();
private:
	// WAIT_TIMES[false] = 60 frames/second, WAIT_TIMES[true] = unlimited frames/second
	const unsigned int WAIT_TIMES[2] {1000 / 60, 0};

	std::shared_ptr<SDL_Window> window;
	std::shared_ptr<SDL_Renderer> renderer;
	std::shared_ptr<TTF_Font> font;
	Settings settings;
	ControlsManager controls_manager;
	std::unique_ptr<Scene> scene;
	bool is_running;

	void import_file (std::string path, std::function<void (SDL_RWops* file, bool is_found)> importer);
	void handle_event ();
	void import_sprite_sheets ();
	void import_tile_sprite_sheet ();
	void import_character_sprite_sheet ();
};

#endif
