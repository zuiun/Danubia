#include <cassert>
#include <filesystem>
#include "game.hpp"

/*
 * Initialises game
 *
 * window = Window
 * renderer = Renderer
 * font = Font
 * 
 * Pre: window != null, renderer != null, font != null
 * Post: None
 * Return: None
 */
Game::Game (std::shared_ptr<SDL_Window> const window, std::shared_ptr<SDL_Renderer> const renderer, std::shared_ptr<TTF_Font> const font) :
	window {window},
	renderer {renderer},
	font {font} {
	assert (window != nullptr);
	assert (renderer != nullptr);
	assert (font != nullptr);

	// Import settings
	import_file (SETTINGS_PATH, [&] (SDL_RWops* file, bool is_found) -> void {
		unsigned char packed_settings {0};

		// Read saved settings
		if (is_found) {
			if (SDL_RWread (file, &packed_settings, sizeof (unsigned char), 1)) {
				settings.is_unlimited_frame_rate = packed_settings & settings.Masks::UNLIMITED_FRAME_RATE;
				settings.is_fullscreen = packed_settings & settings.Masks::FULLSCREEN;
			} else {
				std::cout << SETTINGS_PATH << " read error: " << SDL_GetError () << std::endl;
			}
		// Write default settings
		} else {
			if (settings.is_unlimited_frame_rate) {
				packed_settings |= settings.Masks::UNLIMITED_FRAME_RATE;
			}

			if (settings.is_fullscreen) {
				packed_settings |= settings.Masks::FULLSCREEN;
			}

			if (!SDL_RWwrite (file, &packed_settings, sizeof (unsigned char), 1)) {
				std::cout << SETTINGS_PATH << " write error: " << SDL_GetError () << std::endl;
			}
		}
	});
}

/*
 * Generic importer function for files
 * Creates path folders if they do not exist
 *
 * path = Path to file
 * importer = Importer function; converts file to object if is_found, writes default object to file otherwise
 *
 * Pre: importer != null
 * Post: None
 * Return: None
 */
void Game::import_file (std::string const& path, std::function<void (SDL_RWops* file, bool is_found)> const& importer) {
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
 * Updates game state
 *
 * Pre: scene != NULL
 * Post: None
 * Return: None
 */
void Game::update () {
	// assert (scene != NULL);

	SDL_Event event {};
	unsigned int frame_time {SDL_GetTicks ()};

	while (SDL_PollEvent (&event)) {
		if (event.type == SDL_QUIT) {
			is_running = false;
			return;
		} else {
			scene.handle_event (event);
		}
	}

	scene.update ();
	frame_time = SDL_GetTicks () - frame_time;

	if (frame_time < WAIT_TIMES[settings.is_unlimited_frame_rate]) {
		SDL_Delay (frame_time);
	}
}

bool Game::get_is_running () {
	return is_running;
}
