#include <cassert>
#include <filesystem>
#include "game.hpp"

/*
 * Initialises game
 *
 * width = Width of window
 * height = Height of window
 */
Game::Game (std::shared_ptr<SDL_Window> window, std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<TTF_Font> font) :
	window {window},
	renderer {renderer},
	font {font},
	settings {},
	controls_manager {},
	scenes {},
	scene {},
	is_running {true} {
	// Import settings
	import_file ("saves/settings.bin", [this] (SDL_RWops* file, bool is_found) -> void {
		if (is_found) {
			SDL_RWread (file, &settings.is_unlimited_frame_rate, sizeof (bool), 1);
			SDL_RWread (file, &settings.is_fullscreen, sizeof (bool), 1);
		} else {
			SDL_RWwrite (file, &settings.is_unlimited_frame_rate, sizeof (bool), 1);
			SDL_RWwrite (file, &settings.is_fullscreen, sizeof (bool), 1);
		}
	});
}

/*
 * Generic importer function for files
 * Creates path folders if they do not exist
 *
 * path = Path to file
 * importer = Importer function
 *
 * Pre: importer != null
 * Post: None
 * Return: None
 */
void Game::import_file (std::string path, std::function<void (SDL_RWops* file, bool is_found)> importer) {
	assert (importer != NULL);

	std::string folders {path.substr (0, path.find_last_of ('/'))};
	SDL_RWops* file {};

	// Create path folders if they do not exist 
	std::filesystem::create_directories (folders);
	file = SDL_RWFromFile (path.c_str (), "r+b");

	if (file) {
		importer (file, true);
		SDL_RWclose (file);
	} else {
		std::cout << path << " open error: " << SDL_GetError () << std::endl;
		file = SDL_RWFromFile (path.c_str (), "w+b");

		if (file) {
			importer (file, false);
			SDL_RWclose (file);
			std::cout << path << " created" << std::endl;
		} else {
			std::cout << path << " creation error: " << SDL_GetError () << std::endl;
		}
	}
}

/*
 * Handles input events
 *
 * Pre: None
 * Post: None
 * Return: None
 */
void Game::handle_event () {
	SDL_Event event;

	if (SDL_PollEvent (&event)) {
		switch (event.type) {
			case SDL_QUIT:
				is_running = false;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				controls_manager.handle_input (event);
				break;
			default:
				break;
		}
	}
}

/*
 * Updates game state
 *
 * Pre: None
 * Post: None
 * Return: None
 */
void Game::update () {
	// TODO: Consider moving to scene update?
	unsigned int frame_time = SDL_GetTicks ();

	handle_event ();
	// scenes.at (scene).update ();
	frame_time = SDL_GetTicks () - frame_time;

	if (frame_time < WAIT_TIMES[settings.is_unlimited_frame_rate]) {
		SDL_Delay (frame_time);
	}
}

bool Game::get_is_running () {
	return is_running;
}

void Game::import_sprite_sheets () {
	// Texture import code
	/*
	SDL_Surface* image = IMG_Load (path.c_str ());

	if (image) {
		SDL_SetColorKey (image, SDL_TRUE, SDL_MapRGB (image->format, 0, 255, 255));
		this->sheet = SDL_CreateTextureFromSurface (renderer, image);

		if (sheet) {
			this->width = image->w;
			this->height = image->h;
		} else {
			std::cout << path << " texture creation error: " << SDL_GetError () << std::endl;
		}

		SDL_FreeSurface (image);
		image = nullptr;
	} else {
		std::cout << path << " load error: " << SDL_GetError () << std::endl;
	}
	*/
}

void Game::import_tile_sprite_sheet () {

}

void Game::import_character_sprite_sheet () {

}
