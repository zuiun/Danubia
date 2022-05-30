#pragma once
#ifndef MEDIA_MANAGER_HPP
#define MEDIA_MANAGER_HPP

#include <deque>
#include <vector>
#include <SDL.h>
#include "game_object.hpp"
#include "texture.hpp"

/*
 * Responsible for managing graphics and audio
 */
class MediaManager {
public:
	MediaManager (SDL_Renderer* renderer, std::vector<GameObject*>* game_objects);
	~MediaManager ();
	void render ();
	std::deque<GameObject::RenderRequest*>* get_render_requests ();
	SDL_Renderer* get_renderer ();
private:
	SDL_Renderer* renderer;
	std::deque<GameObject::RenderRequest*>* render_requests;
	std::vector<GameObject*>* game_objects;
};

#endif
