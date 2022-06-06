#include <cassert>
#include <iostream>
#include "controls_manager.hpp"

/*
 * Initialises a controls manager
 */
ControlsManager::ControlsManager () {
	input_buffers.fill (HeldInputs::BUFFER);
}

/*
 * Handles input
 * 
 * Pre: &input != nullptr
 * Post: None
 * Return: None
 */
void ControlsManager::handle_input (SDL_Event const& input) {
	assert (&input != nullptr);

	// Inputs that can be held
	switch (input.type) {
		case SDL_KEYDOWN:
			switch (input.key.keysym.sym) {
				// Up
				case SDLK_w:
				case SDLK_UP:
					handle_held_input (HeldInputs::UP);
					break;
				// Down
				case SDLK_s:
				case SDLK_DOWN:
					handle_held_input (HeldInputs::DOWN);
					break;
				// Left
				case SDLK_a:
				case SDLK_LEFT:
					handle_held_input (HeldInputs::LEFT);
					break;
				// Right
				case SDLK_d:
				case SDLK_RIGHT:
					handle_held_input (HeldInputs::RIGHT);
					break;
				// Skip
				case SDLK_LALT:
				case SDLK_BACKSLASH:
					handle_held_input (HeldInputs::SKIP);
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
					input_buffers[HeldInputs::UP] = HeldInputs::BUFFER;
					// Stop moving up
					break;
				// Down
				case SDLK_s:
				case SDLK_DOWN:
					input_buffers[HeldInputs::DOWN] = HeldInputs::BUFFER;
					// Stop moving down
					break;
				// Left
				case SDLK_a:
				case SDLK_LEFT:
					input_buffers[HeldInputs::LEFT] = HeldInputs::BUFFER;
					// Stop moving left
					break;
				// Right
				case SDLK_d:
				case SDLK_RIGHT:
					input_buffers[HeldInputs::RIGHT] = HeldInputs::BUFFER;
					// Stop moving right
					break;
				// Skip
				case SDLK_LALT:
				case SDLK_BACKSLASH:
					input_buffers[HeldInputs::SKIP] = HeldInputs::BUFFER;
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
		// TODO: Mouse support will probably come a long time later
		case SDL_MOUSEMOTION:
			// Move selector
			break;
		case SDL_MOUSEBUTTONDOWN:
			// Most likely do nothing
			break;
		case SDL_MOUSEBUTTONUP:
			// Do action that selector is on
			break;
		// TODO: Gamepad support will probably come a long time later, but integrate handling with keyboard
		case SDL_JOYAXISMOTION:
			break;
		case SDL_JOYBUTTONDOWN:
			break;
		case SDL_JOYBUTTONUP:
			break;
		case SDL_CONTROLLERAXISMOTION:
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			break;
		case SDL_CONTROLLERBUTTONUP:
			break;
	}
}

void ControlsManager::handle_held_input (HeldInputs input) {
	if (input_buffers[input]) {
		input_buffers[input]--;
	}

	if (!input_buffers[input]) {
		switch (input) {
			// Up
			case HeldInputs::UP:
				break;
			// Down
			case HeldInputs::DOWN:
				break;
			// Left
			case HeldInputs::LEFT:
				break;
			// Right
			case HeldInputs::RIGHT:
				break;
			// Skip
			case HeldInputs::SKIP:
				break;
			default:
				break;
		}
	}
}
