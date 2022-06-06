#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "game.hpp"

/*
 * Runs game
 * 
 * Pre: None
 * Post: None
 * Return: -1 on failed graphics initialisation, 0 otherwise
 */
int main (int argv, char** args) {
	int result {-1};

	// Initialise graphics
	// SDL_Init () returns 0 on success
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK)) {
		std::cout << "SDL initialisation error: " << SDL_GetError () << std::endl;
	} else {
		std::shared_ptr<SDL_Window> window {SDL_CreateWindow ("Danubia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN), SDL_DestroyWindow};
		std::shared_ptr<SDL_Renderer> renderer {};
		std::shared_ptr<TTF_Font> font {};

		if (SDL_NumJoysticks ()) {
			if (SDL_IsGameController (0)) {
				std::shared_ptr<SDL_GameController> controller {SDL_GameControllerOpen (0), SDL_GameControllerClose};

				if (!controller) {
					std::cout << "Gamepad open error: " << SDL_GetError () << std::endl;
				}
			} else {
				std::shared_ptr<SDL_Joystick> joystick {SDL_JoystickOpen (0), SDL_JoystickClose};

				if (!joystick) {
					std::cout << "Gamepad open error: " << SDL_GetError () << std::endl;
				}
			}
		} else {
			std::cout << "No gamepad connected" << std::endl;
		}

		if (window) {
			renderer.reset (SDL_CreateRenderer (window.get (), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
			
			if (renderer) {
				// IMG_Init () returns intialised flags (1) on success
				if (IMG_Init (IMG_INIT_PNG) & IMG_INIT_PNG) {
					// Mix_OpenAudio () returns 0 on success
					if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
						std::cout << "SDL_mixer initialisation error: " << Mix_GetError () << std::endl;
					} else {
						// TTF_Init () returns 0 on success
						if (TTF_Init ()) {
							std::cout << "SDL_ttf initialisation error: " << TTF_GetError () << std::endl;
						} else {
							font.reset (TTF_OpenFont ("assets/lazy.ttf", 16), TTF_CloseFont);

							// Graphics initialised; run game
							if (font.get ()) {
								Game game {window, renderer, font};

								while (game.get_is_running ()) {
									game.update ();
								}

								result = 0;
							} else {
								std::cout << "Font initialisation error: " << TTF_GetError () << std::endl;
							}
						}
					}
				} else {
					std::cout << "SDL_image initialisation error: " << IMG_GetError () << std::endl;
				}
			} else {
				std::cout << "Renderer initialisation error: " << SDL_GetError () << std::endl;
			}
		} else {
			std::cout << "Window initialisation error: " << SDL_GetError () << std::endl;
		}
	}
	
	// Destroy graphics
	TTF_Quit ();
	Mix_Quit ();
	IMG_Quit ();
	SDL_Quit ();
	return result;
}
