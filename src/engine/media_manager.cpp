#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "media_manager.hpp"

/*
 * Initialises media manager
 *
 * window = Window
 * 
 * Pre: window != null
 * Post: None
 * Retrun: None
 */
MediaManager::MediaManager (SDL_Window* window) {
	this->renderer = NULL;

	if (window) {
		this->renderer = SDL_CreateRenderer (window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
		} else {
			std::cout << "Renderer initialisation error: " << SDL_GetError () << std::endl;
		}
	} else {
		std::cout << "window != null" << std::endl;
	}
}

/*
 * Destroys media manager
 *
 * Pre: window != null
 * Post: None
 * Retrun: None
 */
MediaManager::~MediaManager () {
	SDL_DestroyRenderer (renderer);
	this->renderer = NULL;
}

/*
 * Renders window
 *
 * Pre: renderer != null
 * Post: None
 * Return: None
 */
void MediaManager::render () {
	// Draw to the screen using SDL_RenderCopy ();
	if (renderer) {
		if (!SDL_RenderClear (renderer)) {
			SDL_RenderPresent (renderer);
		} else {
			std::cout << "SDL render error: " << SDL_GetError () << std::endl;
		}
	} else {
		std::cout << "renderer != null" << std::endl;
	}
}
