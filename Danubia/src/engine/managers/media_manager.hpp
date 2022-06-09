#pragma once
#ifndef MEDIA_MANAGER_HPP
#define MEDIA_MANAGER_HPP

#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class MediaManager {
public:
	enum Sprites {

	};
	enum Audio {

	};
	
	MediaManager (std::shared_ptr<SDL_Renderer> const renderer, std::shared_ptr<TTF_Font> const font);
	void render ();
	void play ();
private:
	SDL_Colour const BLACK {0, 0, 0};

	std::shared_ptr<SDL_Renderer> const renderer {};
	std::shared_ptr<TTF_Font> const font {};

	void import_texture (std::string const& path);
	void import_sprite_sheets ();
	void import_audio ();
	void import_media ();
};

#endif
