#include <cassert>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "media_manager.hpp"

/*
 * Initialises media manager
 *
 * renderer = Renderer of window
 * 
 * Pre: renderer != null, game_objects != null
 * Post: None
 * Retrun: None
 */
MediaManager::MediaManager (SDL_Renderer* renderer, std::vector<GameObject*>* game_objects) {
	assert (renderer != NULL);
	assert (game_objects != NULL);

	this->renderer = renderer;
	this->render_requests = new std::deque<GameObject::RenderRequest*> ();
	this->game_objects = game_objects;

	if (renderer) {
		SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	} else {
		std::cout << "Renderer initialisation error: " << SDL_GetError () << std::endl;
	}
}

/*
 * Destroys media manager
 *
 * Pre: None
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
	assert (renderer != NULL);

	if (!SDL_RenderClear (renderer)) {
		while (render_requests->size () > 0) {
			GameObject::RenderRequest* render_request = render_requests->front ();

			SDL_RenderCopy (renderer, render_request->texture->get_sheet (), render_request->sprite, render_request->destination);
			render_requests->pop_front ();
		}

		SDL_RenderPresent (renderer);
	} else {
		std::cout << "SDL render error: " << SDL_GetError () << std::endl;
	}
}

std::deque<GameObject::RenderRequest*>* MediaManager::get_render_requests () {
	return render_requests;
}

SDL_Renderer* MediaManager::get_renderer () {
	return renderer;
}
