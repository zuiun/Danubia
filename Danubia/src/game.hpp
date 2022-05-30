#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <SDL.h>
#include "engine\controls_manager.hpp"
#include "engine\game_object.hpp"
#include "engine\media_manager.hpp"

namespace timing {
	/*
	 * Choose between THIRTY, SIXTY, or UNLIMITED frames/second
	 * Used as an index for wait_times
	 */
	enum FrameRate {
		THIRTY,
		SIXTY,
		UNLIMITED,
		LENGTH
	};

	const unsigned int WAIT_TIMES[FrameRate::LENGTH] = {1000 / 30, 1000 / 60, 0};
}

class Game {
public:
	enum GameState {
		MENU,
		COMBAT,
		DIALOGUE
	};
	struct Settings {
		timing::FrameRate frame_rate;
		bool is_fullscreen;
	};

	Game (unsigned int width = 640, unsigned int height = 480, timing::FrameRate frame_rate = timing::FrameRate::THIRTY);
	~Game ();
	void update ();
	bool get_is_running ();
private:
	SDL_Window* window;
	Settings* settings;
	MediaManager* media_manager;
	ControlsManager* controls_manager;
	GameState game_state;
	std::vector<GameObject*>* game_objects;
	bool is_running;

	bool handle_event ();
};

#endif
