#include <iostream>
#include "game.hpp"

/*
 * Initialises game
 * 
 * width = Width of window
 * height = Height of window
 * frame_rate = New frame rate
 */
Game::Game (unsigned int width, unsigned int height, timing::FrameRate frame_rate) {
	// TODO: Import everything from a settings file
	this->window = NULL;
	this->settings = new Settings ();
	settings->frame_rate = frame_rate;
	settings->is_fullscreen = false;
	this->media_manager = NULL;
	this->controls_manager = new ControlsManager ();
	this->game_state = MENU;
	this->game_objects = new std::vector<GameObject*> ();
	this->is_running = true;

	// Create window
	if (!SDL_Init (SDL_INIT_VIDEO)) {
		window = SDL_CreateWindow ("Danubia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

		if (window) {
			SDL_Renderer* renderer = SDL_CreateRenderer (window, -1, 0);

			// Create game objects
			game_objects->push_back (new GameObject ("default", new Texture (renderer, "assets/press.png"), NULL));
			media_manager = new MediaManager (renderer, game_objects);
		} else {
			std::cout << "Window initialisation error: " << SDL_GetError () << std::endl;
		}
	}
}

/*
 * Destroys game
 */
Game::~Game () {
	// Destroys window
	SDL_DestroyWindow (window);
	window = NULL;
	SDL_Quit ();
	// Destroys game objects
	media_manager->~MediaManager ();
}

/*
 * Handles input events
 * 
 * Pre: None
 * Post: None
 * Return: true if need to render, false otherwise
 */
bool Game::handle_event () {
	SDL_Event event;

	if (SDL_PollEvent (&event)) {
		switch (event.type) {
			case SDL_QUIT:
				is_running = false;
				return false;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				controls_manager->handle_input (event);
				break;
			default:
				media_manager->get_render_requests ()->push_back (game_objects->front ()->request_render (0, 0, NULL));
				break;
		}
	}
	
	return true;
}

/*
 * Updates game state
 * 
 * Pre: None
 * Post: None
 * Return: None
 */
void Game::update () {
	unsigned int frame_time = SDL_GetTicks ();
	bool is_render = handle_event ();

	// If handling event takes too long, don't render this frame
	if ((SDL_GetTicks () - frame_time) < timing::WAIT_TIMES[settings->frame_rate]) {
		if (is_render) {
			media_manager->render ();
		}

		frame_time = SDL_GetTicks () - frame_time;

		if (frame_time < timing::WAIT_TIMES[settings->frame_rate]) {
			SDL_Delay (frame_time);
		}
	}
}

bool Game::get_is_running () {
	return is_running;
}
