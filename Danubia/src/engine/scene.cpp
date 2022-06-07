#include <cassert>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "scene.hpp"
#include "scene_list.hpp"

/*
 * Initialises scene
 *
 * renderer = Renderer of window
 * path = Path to scene file
 *
 * Pre: renderer != nullptr
 * Post: None
 * Return: None
 */
Scene::Scene (std::shared_ptr<SDL_Renderer> const renderer, unsigned int const scene) :
	type {scenes[scene].type},
	renderer {renderer},
	grid {},
	ui_manager {} {
	assert (renderer != nullptr);

	SDL_SetRenderDrawColor (renderer.get (), 255, 255, 255, SDL_ALPHA_OPAQUE);
	// TODO: Import scene from path
	// This would involve listing the involved GameObjects, Characters, and Tiles, which would probably need to be listed in an enum or something

	/*
	for (unsigned int i = 0; i < width; i++) {
		grid.push_back ({});

		for (unsigned int j = 0; j < height; j++) {
			grid.back ().push_back ({NULL});
		}
	}
	*/
}

void Scene::handle_event (SDL_Event const& event) {
	switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			controls_manager.handle_input (event);
			break;
		default:
			break;
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
		// TODO: Render UI (includes text)

		SDL_Surface* text_surface = TTF_RenderText_Solid (font.get (), "text", BLACK);

		// Text render code
		/*
		if (text_surface) {
			std::unique_ptr<SDL_Texture> text_texture {SDL_CreateTextureFromSurface (renderer, text_surface), SDL_FreeSurface};
			
			if (text_texture) {
				// Render text
				SDL_RenderCopy (renderer, text_texture, sprite, destination);
			} else {
				std::cout << "Text texture creation error: " << SDL_GetError () << std::endl;
			}
		} else {
			std::cout << "Text render error: " << TTF_GetError () << std::endl;
		}
		*/

		// SDL_RenderCopy (renderer, texture, sprite, destination);
		SDL_RenderPresent (renderer.get ());
	} else {
		std::cout << "Renderer clear error: " << SDL_GetError () << std::endl;
	}
}

void Scene::update () {
	switch (type) {
		case MENU:
			break;
		case GAMEPLAY:
			while (turns.at (turn % turns.size ()).empty ()) {
				turn++;
			}

			for (Character i : turns.at (turn % turns.size ())) {
				i.expire_modifiers ();

				if (i.get_is_player ()) {
					// TODO: Player action
					player_turns++;
				} else {
					// TODO: Computer action
				}

				i.time_modifiers ();
				true_turns++;
			}

			turn++;
			break;
	}
	
	render ();
}
