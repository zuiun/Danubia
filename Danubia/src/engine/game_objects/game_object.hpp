#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <memory>
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
		std::shared_ptr<SDL_Texture> texture {};
		std::vector<SDL_Rect> sprites {};
	};
	struct RenderInformation {
		std::shared_ptr<SDL_Texture> texture {};
		std::shared_ptr<SDL_Rect> sprite {};

		RenderInformation (SpriteSheet sprite_sheet, unsigned int sprite) :
			texture {sprite_sheet.texture},
			sprite {std::make_shared<SDL_Rect> (sprite_sheet.sprites.at (sprite))} {
		}
	};

	GameObject (std::string path);
	RenderInformation create_render_information ();
	void animate ();
private:
	static unsigned int const BUFFER {4};
	std::vector<SpriteSheet> sprite_sheets {};
	unsigned int sheet {0};
	unsigned int sprite {0};
	unsigned int frame_buffer {BUFFER};
	bool is_visible {true};
};

#endif
