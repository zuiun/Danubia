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
	
	MediaManager (std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<TTF_Font> font);
	void render ();
	void play ();
private:
	std::shared_ptr<SDL_Renderer> renderer {};
	std::shared_ptr<TTF_Font> font {};

	void import_texture (std::string const& path);
	void import_sprite_sheets ();
	void import_audio ();
	void import_media ();
};

#endif
