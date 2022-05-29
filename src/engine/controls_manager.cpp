#include <iostream>
#include "controls_manager.hpp"

ControlsManager::ControlsManager () {
	std::fill (this->input_buffers, this->input_buffers + held_inputs::LENGTH, held_inputs::BUFFER);
}

void ControlsManager::handle_input (SDL_Event input) {
	// Inputs that can be held
	switch (input.type) {
		case SDL_KEYDOWN:
			switch (input.key.keysym.sym) {
				// Up
				case SDLK_w:
				case SDLK_UP:
					if (input_buffers[held_inputs::UP]) {
						input_buffers[held_inputs::UP]--;
					}

					if (!input_buffers[held_inputs::UP]) {
						// Move up
					}

					break;
				// Down
				case SDLK_s:
				case SDLK_DOWN:
					if (input_buffers[held_inputs::DOWN]) {
						input_buffers[held_inputs::DOWN]--;
					}

					if (!input_buffers[held_inputs::DOWN]) {
						// Move down
					}

					break;
				// Left
				case SDLK_a:
				case SDLK_LEFT:
					if (input_buffers[held_inputs::LEFT]) {
						input_buffers[held_inputs::LEFT]--;
					}

					if (!input_buffers[held_inputs::LEFT]) {
						// Move left
					}

					break;
				// Right
				case SDLK_d:
				case SDLK_RIGHT:
					if (input_buffers[held_inputs::RIGHT]) {
						input_buffers[held_inputs::RIGHT]--;
					}

					if (!input_buffers[held_inputs::RIGHT]) {
						// Move right
					}

					break;
				// Skip
				case SDLK_LALT:
				case SDLK_BACKSLASH:
					if (input_buffers[held_inputs::SKIP]) {
						input_buffers[held_inputs::SKIP]--;
					}

					if (!input_buffers[held_inputs::SKIP]) {
						// Skip text/actions
					}

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
