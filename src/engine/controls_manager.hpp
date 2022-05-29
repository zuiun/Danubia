#pragma once
#ifndef CONTROLS_MANAGER_HPP
#define CONTROLS_MANAGER_HPP

#include <SDL.h>

namespace held_inputs {
	enum HeldInputs {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SKIP,
		LENGTH,
		BUFFER = 10
	};
}

class ControlsManager {
public:
	ControlsManager ();
	~ControlsManager ();
	void handle_input (SDL_Event input);
private:
	unsigned int input_buffers[held_inputs::LENGTH];
};

#endif
