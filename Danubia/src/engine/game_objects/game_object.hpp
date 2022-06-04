#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

class GameObject {
public:
	/*
	 * Stores information for an individual sprite sheet
	 * One sprite sheet per animation set
	 */
	struct SpriteSheet {
		SDL_Texture* texture;
		std::vector<SDL_Rect*>* sprites;
	};
	struct RenderInformation {
		SDL_Texture* texture;
		SDL_Rect* sprite;
	};

	GameObject (std::string path);
	~GameObject ();
	RenderInformation* create_render_information ();
	void animate ();
private:
	static const unsigned int BUFFER = 5;
	std::vector<SpriteSheet*>* sprite_sheets;
	unsigned int sheet;
	unsigned int sprite;
	unsigned int frame_buffer;
	bool is_visible;
};

#endif
