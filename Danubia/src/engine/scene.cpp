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
Scene::Scene (std::shared_ptr<SDL_Renderer> renderer, unsigned int width, unsigned int height) :
	renderer {renderer},
	grid {},
	ui_manager {} {
	assert (renderer != nullptr);

	// TODO: Import scene from file?
	// This would involve listing the involved GameObjects and Tiles, which would probably need to be listed in an enum or something
	SDL_SetRenderDrawColor (renderer.get (), 255, 255, 255, 255);

	for (unsigned int i = 0; i < width; i++) {
		grid.push_back ({});
		
		for (unsigned int j = 0; j < height; j++) {
			grid.back ().push_back ({NULL});
		}
	}
}

/*
 * Renders window
 *
 * Pre: renderer != nullptr
 * Post: None
 * Return: None
 */
void Scene::render () {
	assert (renderer);

	if (!SDL_RenderClear (renderer.get ())) {
		// TODO: Render grid
		// TODO: Render UI

		SDL_Surface* text_surface = TTF_RenderText_Solid (font.get (), "text", BLACK);

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
		SDL_RenderPresent (renderer.get ());
	} else {
		std::cout << "Renderer clear error: " << SDL_GetError () << std::endl;
	}
}

void Scene::update () {

}
