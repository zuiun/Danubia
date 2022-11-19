#include <cassert>
#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "game.hpp"

/*
 * Initialises SDL
 *
 * Pre: None
 * Post: None
 * Return: true on success, false on failure
 */
bool initialise_sdl () {
	// SDL_Init () returns 0 on success
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK)) {
		std::cout << "SDL initialisation error: " << SDL_GetError () << std::endl;
	} else {
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
			std::cout << "No gamepad detected" << std::endl;
		}

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
					return true;
				}
			}
		} else {
			std::cout << "SDL_image initialisation error: " << IMG_GetError () << std::endl;
		}
	}

	return false;
}

/*
 * Imports sprite
 *
 * path = Path
 * renderer = Renderer
 *
 * Pre: renderer != null
 * Post: None
 * Return: true on success, false on failure
 */
bool import_sprite (std::string const& path, std::shared_ptr<SDL_Renderer> renderer) {
	assert (renderer != nullptr);

	std::unique_ptr<SDL_Surface, decltype (&SDL_FreeSurface)> image {IMG_Load (path.c_str ()), SDL_FreeSurface};

	if (image) {
		SDL_SetColorKey (image.get (), SDL_TRUE, SDL_MapRGB (image->format, 0, 255, 255));

		std::shared_ptr<SDL_Texture> sheet {SDL_CreateTextureFromSurface (renderer.get (), image.get ()), SDL_DestroyTexture};

		if (sheet) {
			// TODO: Move into texture database
			return true;
		} else {
			std::cout << "Texture " << path << " creation error : " << SDL_GetError () << std::endl;
		}
	} else {
		std::cout << "Sprite " << path << " import error: " << SDL_GetError () << std::endl;
	}

	return false;
}

/*
 * Imports graphics
 *
 * renderer = Renderer
 *
 * Pre: renderer != null
 * Post: None
 * Return: true on success, false on failure
 */
bool import_graphics (std::shared_ptr<SDL_Renderer> renderer) {
	assert (renderer != nullptr);
	// import_sprite ("graphics/", renderer);
	// std::cout << "Graphics import error" << std::endl;
	return true;
}

/*
 * Imports music
 *
 * Pre: None
 * Post: None
 * Return: true on success, false on failure
 */
bool import_music (std::string const& path) {
	std::unique_ptr <Mix_Music, decltype (&Mix_FreeMusic)> music {Mix_LoadMUS (path.c_str ()), Mix_FreeMusic};

	if (music) {
		return true;
	} else {
		std::cout << "Music " << path << " import error: " << Mix_GetError () << std::endl;
		return false;
	}
}

/*
 * Imports sound (effects)
 *
 * Pre: None
 * Post: None
 * Return: true on success, false on failure
 */
bool import_sound (std::string const& path) {
	std::unique_ptr <Mix_Chunk, decltype (&Mix_FreeChunk)> chunk {Mix_LoadWAV (path.c_str ()), Mix_FreeChunk};

	if (chunk) {
		return true;
	} else {
		std::cout << "Sound " << path << " import error: " << Mix_GetError () << std::endl;
		return false;
	}
}

/*
 * Imports audio
 *
 * Pre: None
 * Post: None
 * Return: true on success, false on failure
 */
bool import_audio () {
	// return import_music ("audio/music/") && import_sound ("audio/sound/");
	// std::cout << "Audio import error" << std::endl;
	return true;
}

// TODO: Add an actual arguments list, such as for debugging
// SDL needs argv and args, which are unused
#pragma warning (disable: 4100)
/*
 * Runs game
 * 
 * argv = Never used, but necessary for SDL
 * args = Never used, but necessary for SDL
 * 
 * Pre: None
 * Post: None
 * Return: -1 on failed initialisation or importation, 0 otherwise
 */
int main (int argv, char* args[]) {
	int result {-1};
	
	if (initialise_sdl () && import_audio ()) {
		std::shared_ptr<SDL_Window> window {SDL_CreateWindow ("Danubia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN), SDL_DestroyWindow};
		
		if (window) {
			std::shared_ptr<SDL_Renderer> renderer {SDL_CreateRenderer (window.get (), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer};

			if (renderer && import_graphics (renderer)) {
				std::shared_ptr<TTF_Font> font {TTF_OpenFont ("assets/fonts/GentiumPlus-Regular.ttf", 16), TTF_CloseFont};

				// Everything initialised; run game
				if (font) {
					Game game {window, renderer, font};

					while (game.get_is_running ()) {
						game.update ();
					}
					
					result = 0;
				} else {
					std::cout << "Font initialisation error: " << TTF_GetError () << std::endl;
				}
			} else {
				std::cout << "Renderer initialisation error: " << SDL_GetError () << std::endl;
			}
		} else {
			std::cout << "Window initialisation error: " << SDL_GetError () << std::endl;
		}
	}

	TTF_Quit ();
	Mix_Quit ();
	IMG_Quit ();
	SDL_Quit ();
	return result;
}
