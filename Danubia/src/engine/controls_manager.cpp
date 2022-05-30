#include <cassert>
#include <iostream>
#include "controls_manager.hpp"

/*
 * Initialises a controls manager
 */
ControlsManager::ControlsManager () {
	std::fill (this->input_buffers, this->input_buffers + held_inputs::LENGTH, held_inputs::BUFFER);
}

/*
 * Handles input
 * 
 * Pre: &input != null
 * Post: None
 * Return: None
 */
void ControlsManager::handle_input (SDL_Event input) {
	assert (&input != NULL);

	// Inputs that can be held
	switch (input.type) {
		case SDL_KEYDOWN:
			switch (input.key.keysym.sym) {
				// Up
				case SDLK_w:
				case SDLK_UP:
					handle_held_input (held_inputs::UP);
					break;
				// Down
				case SDLK_s:
				case SDLK_DOWN:
					handle_held_input (held_inputs::DOWN);
					break;
				// Left
				case SDLK_a:
				case SDLK_LEFT:
					handle_held_input (held_inputs::LEFT);
					break;
				// Right
				case SDLK_d:
				case SDLK_RIGHT:
					handle_held_input (held_inputs::RIGHT);
					break;
				// Skip
				case SDLK_LALT:
				case SDLK_BACKSLASH:
					handle_held_input (held_inputs::SKIP);
					break;
				default:
					break;
			}

			break;
		// All inputs
		case SDL_KEYUP:
			switch (input.key.keysym.sym) {
				// Up
				case SDLK_w:
				case SDLK_UP:
					input_buffers[held_inputs::UP] = held_inputs::BUFFER;
					// Stop moving up
					break;
				// Down
				case SDLK_s:
				case SDLK_DOWN:
					input_buffers[held_inputs::DOWN] = held_inputs::BUFFER;
					// Stop moving down
					break;
				// Left
				case SDLK_a:
				case SDLK_LEFT:
					input_buffers[held_inputs::LEFT] = held_inputs::BUFFER;
					// Stop moving left
					break;
				// Right
				case SDLK_d:
				case SDLK_RIGHT:
					input_buffers[held_inputs::RIGHT] = held_inputs::BUFFER;
					// Stop moving right
					break;
				// Skip
				case SDLK_LALT:
				case SDLK_BACKSLASH:
					input_buffers[held_inputs::SKIP] = held_inputs::BUFFER;
					// Stop skipping text/actions
					break;
				// Confirm
				case SDLK_z:
				case SDLK_RETURN:
					break;
				// Cancel
				case SDLK_x:
				case SDLK_RSHIFT:
					break;
				// Menu
				case SDLK_c:
				case SDLK_RCTRL:
					break;
				// Zoom in
				case SDLK_q:
				case SDLK_LEFTBRACKET:
					break;
				// Zoom out
				case SDLK_e:
				case SDLK_RIGHTBRACKET:
					break;
				default:
					break;
			}

			break;
	}
}

void ControlsManager::handle_held_input (held_inputs::HeldInputs input) {
	if (input_buffers[input]) {
		input_buffers[input]--;
	}

	if (!input_buffers[input]) {
		switch (input) {
			// Up
			case held_inputs::UP:
				break;
			// Down
			case held_inputs::DOWN:
				break;
			// Left
			case held_inputs::LEFT:
				break;
			// Right
			case held_inputs::RIGHT:
				break;
			// Skip
			case held_inputs::SKIP:
				break;
			default:
				break;
		}
	}
}
