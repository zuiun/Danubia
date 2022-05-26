#include <chrono>
#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include "game.hpp"
#include "time_manager.hpp"

/*
 * Initialises game
 * 
 * width = Width of screen
 * height = Height of screen
 * frame_rate = New frame rate
 */
Game::Game (int width, int height, int frame_rate) {
	this->time_manager = new TimeManager (frame_rate);
	this->is_running = true;

	// Creates window
	if (!SDL_Init (SDL_INIT_VIDEO)) {
		window = SDL_CreateWindow ("Danubia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

		if (window) {
			renderer = SDL_CreateRenderer (window, -1, 0);

			if (renderer) {
				SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
				return;
			}
		}
	}

	std::cout << "SDL initialisation error: " << SDL_GetError () << std::endl;
}

/*
 * Destroys game
 * 
 * Pre: None
 * Post: None
 */
Game::~Game () {
	// Destroys window
	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (window);
	SDL_Quit ();
}

/*
 * Handles input events
 * 
 * Pre: None
 * Post: None
 * Return: None
 */
void Game::handle_event () {
	if (SDL_PollEvent (&event)) {
		switch (event.type) {
			case SDL_QUIT:
				is_running = false;
				break;
			default:
				break;
		}
	}
}

/*
 * Renders window
 * 
 * Pre: renderer != NULL
 * Post: None
 * Return: None
 */
void Game::render () {
	if (renderer) {
		if (!SDL_RenderClear (renderer)) {
			SDL_SetRenderDrawColor (renderer, rand () % 256, rand () % 256, rand () % 256, 255);
			SDL_RenderPresent (renderer);
		} else {
			std::cout << "SDL render error: " << SDL_GetError () << std::endl;
		}
	} else {
		std::cout << "renderer != null" << std::endl;
	}
}

/*
 * Updates game state
 * 
 * Pre: renderer != null
 * Post: None
 * Return: None
 */
void Game::update () {
	handle_event ();

	TimeManager::FrameInformation* frame_information = time_manager->get_frame_information ();

	if (!frame_information->is_skip_frame) {
		render ();
	}
	
	SDL_Delay (frame_information->wait_time);
}

bool Game::get_is_running () {
	return is_running;
}
