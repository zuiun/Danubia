#include <cassert>
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
	media_manager {renderer, font} {
	// TODO: Import scene
	// This would involve listing the involved  map, Characters, and Tiles, which would probably need to be listed in an enum or something

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
	/*
	// TODO: Animate Objects
	if (frame_buffer > 0) {
		frame_buffer--;
	} else {
		frame_buffer = BUFFER;
		sprite = (sprite + 1) % sprite_sheets.at (sheet).sprites.size ();
	}
	*/

	switch (type) {
		case scene_objects::SceneData::Type::MENU:
			break;
		case scene_objects::SceneData::Type::GAMEPLAY:
			while (turns.at (turn % turns.size ()).empty ()) {
				turn++;
			}

			for (Character i : turns.at (turn % turns.size ())) {
				character_manager.begin_turn (i);

				if (i.faction == player_faction) {
					// TODO: Player action on the 
					character_manager.act (CharacterManager::Actions::AI, i);
					player_turns++;
				} else {
					character_manager.act (CharacterManager::Actions::AI, i);
				}

				character_manager.end_turn (i);
				true_turns++;
			}

			turn++;
			break;
	}
	
	media_manager.render ();
}
