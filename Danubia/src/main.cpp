#include "game.hpp"

/*
 * Runs game
 * 
 * Pre: None
 * Post: None
 * Return: 1 on failed graphics initialisation, 0 otherwise
 */
int main () {
	SDL_Window* window {};
	SDL_Renderer* renderer {};
	TTF_Font* font {};
	bool success = initialise_graphics (window, renderer, font);

	if (success) {
		Game game {window, renderer, font};

		while (game.get_is_running ()) {
			game.update ();
		}
	}

	destroy_graphics (window, renderer, font);
	return success;
}

/*
 * Initialises graphics
 * 
 * window = Window
 * renderer = Renderer of window
 * font = Font
 * 
 * Pre: None
 * Post: None
 * Return: None
 */
bool initialise_graphics (SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
	// SDL_Init () returns 0 on success
	if (SDL_Init (SDL_INIT_VIDEO)) {
		std::cout << "SDL initialisation error: " << SDL_GetError () << std::endl;
	} else {
		window = SDL_CreateWindow ("Danubia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

		if (window) {
			renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
			
			if (renderer) {
				// IMG_Init () returns intialised flags (1) on success
				if (IMG_Init (IMG_INIT_PNG) & IMG_INIT_PNG) {
					// TTF_Init () returns 0 on success
					if (TTF_Init ()) {
						std::cout << "SDL_ttf initialisation error: " << SDL_GetError () << std::endl;
					} else {
						font = TTF_OpenFont ("assets/lazy.ttf", 16);

						if (font) {
							return true;
						} else {
							std::cout << "Font initialisation error: " << TTF_GetError () << std::endl;
						}
					}
				} else {
					std::cout << "SDL_image initialisation error: " << SDL_GetError () << std::endl;
				}
			} else {
				std::cout << "Renderer initialisation error: " << SDL_GetError () << std::endl;
			}
		} else {
			std::cout << "Window initialisation error: " << SDL_GetError () << std::endl;
		}
	}

	return false;
}

/*
 * Destroys graphics
 * 
 * window = Window
 * renderer = Renderer of window
 * font = Font
 * 
 * Pre: None
 * Post: None
 * Return: None
 */
void destroy_graphics (SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
	if (font) {
		TTF_CloseFont (font);
		TTF_Quit ();
	}

	if (renderer) {
		SDL_DestroyRenderer (renderer);
		IMG_Quit ();
	}

	if (window) {
		SDL_DestroyWindow (window);
		SDL_Quit ();
	}

	delete window;
	delete renderer;
	delete font;
}
