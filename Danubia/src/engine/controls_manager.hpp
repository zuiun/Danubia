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

	std::array<unsigned int, HeldInputs::LENGTH> input_buffers {};

	void handle_held_input (HeldInputs input);
};

#endif
