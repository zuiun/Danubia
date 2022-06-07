#include <cassert>
#include "media_manager.hpp"

/*
 * Initialises media manager
 * 
 * renderer = Renderer
 * font = Font
 * 
 * Pre: renderer != null, font != null
 * Post: None
 * Return: None
 */
MediaManager::MediaManager (std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<TTF_Font> font) :
	renderer {renderer},
	font {font} {
	assert (renderer != nullptr);
	assert (font != nullptr);
}

void MediaManager::render () {

}

void MediaManager::play () {

}

void MediaManager::import_texture (std::string const& path) {
	SDL_Surface* image {IMG_Load (path.c_str ())};

	if (image) {
		SDL_Texture* sheet {};

		SDL_SetColorKey (image, SDL_TRUE, SDL_MapRGB (image->format, 0, 255, 255));
		sheet = SDL_CreateTextureFromSurface (renderer.get (), image);

		if (sheet) {
			// this->width = image->w;
			// this->height = image->h;
		} else {
			std::cout << path << " texture creation error: " << SDL_GetError () << std::endl;
		}

		SDL_FreeSurface (image);
	} else {
		std::cout << path << " load error: " << SDL_GetError () << std::endl;
	}
}

void MediaManager::import_sprite_sheets () {

}

void MediaManager::import_audio () {
	
}

void MediaManager::import_media () {
	
}
