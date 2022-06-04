#include <filesystem>
#include "game.hpp"

/*
 * Initialises game
 *
 * width = Width of window
 * height = Height of window
 */
Game::Game (SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) :
	window {window}, renderer {renderer}, font {font} {
	this->settings = new Settings ();
	this->controls_manager = new ControlsManager ();
	this->scenes = new std::vector<Scene*> ();
	this->scene = nullptr;
	this->is_running = true;

	// Create saves folder if it doesn't exist
	std::filesystem::create_directory ("saves");

	// Import settings
	import_file ("saves/settings.bin", [this] (SDL_RWops* file, bool is_found) -> void {
		if (is_found) {
			SDL_RWread (file, &settings->unlimited_frame_rate, sizeof (bool), 1);
			SDL_RWread (file, &settings->is_fullscreen, sizeof (bool), 1);
		} else {
			SDL_RWwrite (file, &settings->unlimited_frame_rate, sizeof (bool), 1);
			SDL_RWwrite (file, &settings->is_fullscreen, sizeof (bool), 1);
		}
	});
}

/*
 * Generic importer function for files
 *
 * path = Path to file
 * importer = Importer function
 *
 *
 */
void Game::import_file (std::string path, std::function<void (SDL_RWops* file, bool is_found)> importer) {
	SDL_RWops* file = SDL_RWFromFile (path.c_str (), "r+b");

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
				controls_manager->handle_input (event);
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

	// If handling event takes too long, don't render this frame
	if ((SDL_GetTicks () - frame_time) < WAIT_TIMES[settings->unlimited_frame_rate]) {
		// TODO: Scene frame render here
		frame_time = SDL_GetTicks () - frame_time;

		if (frame_time < WAIT_TIMES[settings->unlimited_frame_rate]) {
			SDL_Delay (frame_time);
		}
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
