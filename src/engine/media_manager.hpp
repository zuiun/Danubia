#pragma once
#ifndef MEDIA_MANAGER_HPP
#define MEDIA_MANAGER_HPP

#include <SDL.h>

/*
 * Responsible for managing graphics and audio
 */
class MediaManager {
public:
	MediaManager (SDL_Window* window);
	~MediaManager ();
	void render ();
private:
	SDL_Renderer* renderer;
};

#endif
