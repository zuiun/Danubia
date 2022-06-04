#include <cassert>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "scene.hpp"

/*
 * Initialises scene
 *
 * renderer = Renderer of window
 *
 * Pre: renderer != nullptr
 * Post: None
 * Retrun: None
 */
Scene::Scene (SDL_Renderer* renderer, unsigned int width, unsigned int height) {
	assert (renderer != nullptr);

	// TODO: Import scene from file?
	// This would involve listing the involved GameObjects and Tiles, which would probably need to be listed in an enum or something
	this->renderer = renderer;
	this->grid = new std::vector<std::vector<Tile*>*> ();
	this->ui_manager = nullptr;

	if (renderer) {
		SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	} else {
		std::cout << "Renderer initialisation error: " << SDL_GetError () << std::endl;
	}

	for (unsigned int i = 0; i < width; i++) {
		grid->push_back (new std::vector<Tile*> ());
		
		for (unsigned int j = 0; j < height; j++) {
			grid->back ()->push_back (new Tile (NULL));
		}
	}
}

Scene::~Scene () {
	SDL_DestroyRenderer (renderer);
	renderer = nullptr;
}

/*
 * Renders window
 *
 * Pre: renderer != nullptr
 * Post: None
 * Return: None
 */
void Scene::render () {
	assert (renderer != nullptr);

	if (!SDL_RenderClear (renderer)) {
		// TODO: Render grid
		// TODO: Render UI

		SDL_Surface* text_surface = TTF_RenderText_Solid (font, "text", BLACK);

		// Text render code
		/*
		if (text_surface) {
			SDL_Texture* text_texture = SDL_CreateTextureFromSurface (renderer, text_surface);

			if (text_texture) {
				// Render text
			} else {
				std::cout << "Text texture creation error: " << SDL_GetError () << std::endl;
			}

			SDL_FreeSurface (text_surface);
			text_surface = nullptr;
		} else {
			std::cout << "Text render error: " << TTF_GetError () << std::endl;
		}
		*/

		// SDL_RenderCopyEx
		SDL_RenderPresent (renderer);
	} else {
		std::cout << "Renderer clear error: " << SDL_GetError () << std::endl;
	}
}

void Scene::update () {

}
