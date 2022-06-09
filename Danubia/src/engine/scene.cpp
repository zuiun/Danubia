#include <cassert>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "scene.hpp"

/*
 * Initialises scene
 *
 * renderer = Renderer of window
 * path = Path to scene file
 *
 * Pre: None
 * Post: None
 * Return: None
 */
Scene::Scene (std::shared_ptr<SDL_Renderer> const renderer, std::shared_ptr<TTF_Font> const font, scene_objects::Scenes const scene) :
	type {scene_objects::scenes[scene].type},
	map {},
	media_manager {renderer, font},
	ui_manager {} {
	// TODO: Import scene from path
	// This would involve listing the involved GameObjects, Characters, and Tiles, which would probably need to be listed in an enum or something

	/*
	for (unsigned int i = 0; i < width; i++) {
		map.push_back ({});

		for (unsigned int j = 0; j < height; j++) {
			map.back ().push_back ({NULL});
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

void Scene::update () {
	switch (type) {
		case scene_objects::SceneData::Type::MENU:
			break;
		case scene_objects::SceneData::Type::GAMEPLAY:
			while (turns.at (turn % turns.size ()).empty ()) {
				turn++;
			}

			for (Character i : turns.at (turn % turns.size ())) {
				i.expire_modifiers ();

				if (i.get_faction () == Character::Factions::NATIONAL_LEAGUE) {
					// TODO: Player action on the UI
					std::string response {};

					do {
						std::cout << "Enter a number: ";
						std::cin >> response;
					} while (!std::isdigit (response.front ()));

					// i.act (Character::Actions::AI);
					player_turns++;
				} else {
					i.act (Character::Actions::AI, i);
				}

				i.time_modifiers ();
				true_turns++;
			}

			turn++;
			break;
	}
	
	media_manager.render ();
}
