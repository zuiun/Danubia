#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <vector>
#include <SDL.h>

/*
 * Stores information for an individual sprite sheet
 * One sprite sheet per animation set
 */
struct SpriteSheet {
	// Use reset () to change texture
	std::shared_ptr<SDL_Texture> texture {{}, SDL_DestroyTexture};
	std::vector<SDL_Rect> sprites {};
};

struct RenderInformation {
	unsigned int const BUFFER {4};

	unsigned int sheet {0};
	unsigned int sprite {0};
	unsigned int buffer {BUFFER};
};

struct Object {
	std::vector<SpriteSheet> sprite_sheets {};
	RenderInformation render_information {};
	bool is_visible {true};
};

#endif
