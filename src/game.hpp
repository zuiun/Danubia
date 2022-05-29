#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include "engine\media_manager.hpp"
#include "engine\controls_manager.hpp"

namespace frame_time {
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
		frame_time::FrameRate frame_rate;
		bool is_fullscreen;
	};

	Game (unsigned int width = 640, unsigned int height = 480, frame_time::FrameRate frame_rate = frame_time::FrameRate::THIRTY);
	~Game ();
	void update ();
	bool get_is_running ();
private:
	SDL_Window* window;
	Settings* settings;
	MediaManager* media_manager;
	ControlsManager* controls_manager;
	GameState game_state;
	bool is_running;

	bool handle_event ();
};

#endif
