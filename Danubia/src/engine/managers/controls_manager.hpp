#pragma once
#ifndef CONTROLS_MANAGER_HPP
#define CONTROLS_MANAGER_HPP

#include <array>
#include <SDL.h>

class ControlsManager {
public:
	ControlsManager ();
	void handle_input (SDL_Event const& input);
private:
	enum HeldInputs {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SKIP,
		LENGTH,
		BUFFER = 10
	};

	unsigned int const DEAD_ZONE {1000};

	std::array<unsigned int, HeldInputs::LENGTH> input_buffers {BUFFER, BUFFER, BUFFER, BUFFER, BUFFER};

	void handle_held_input (HeldInputs input);
};

#endif
