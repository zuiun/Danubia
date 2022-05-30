#include <cassert>
#include <SDL_image.h>
#include "texture.hpp"

/*
 * Initialises texture
 * 
 * renderer = Renderer
 * path = Path to sprite sheet
 * 
 * Pre: renderer != null
 * Post: None
 */
Texture::Texture (SDL_Renderer* renderer, std::string path) {
	assert (renderer != NULL);
	this->sheet = NULL;
	this->width = 0;
	this->height = 0;

	SDL_Surface* image = IMG_Load (path.c_str ());

	if (image) {
		SDL_SetColorKey (image, SDL_TRUE, SDL_MapRGB (image->format, 0, 255, 255));
		this->sheet = SDL_CreateTextureFromSurface (renderer, image);

		if (sheet) {
			this->width = image->w;
			this->height = image->h;
		} else {
			std::cout << path << " texture creation error: " << SDL_GetError () << std::endl;
		}

		SDL_FreeSurface (image);
		image = NULL;
	} else {
		std::cout << path << " load error: " << SDL_GetError () << std::endl;
	}
}

Texture::~Texture () {
	if (sheet) {
		SDL_DestroyTexture (sheet);
		sheet = NULL;
	}
}

SDL_Texture* Texture::get_sheet () {
	return sheet;
}

unsigned int Texture::get_width () {
	return width;
}

unsigned int Texture::get_height () {
	return height;
}
