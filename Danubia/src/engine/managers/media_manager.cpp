#include <cassert>
#include <iostream>
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
MediaManager::MediaManager (std::shared_ptr<SDL_Renderer> const renderer, std::shared_ptr<TTF_Font> const font) :
	renderer {renderer},
	font {font} {
	assert (renderer != nullptr);
	assert (font != nullptr);
	
	SDL_SetRenderDrawColor (renderer.get (), 255, 255, 255, SDL_ALPHA_OPAQUE);
}

/*
 * Renders window
 *
 * Pre: None
 * Post: None
 * Return: None
 */
void MediaManager::render () {
	if (!SDL_RenderClear (renderer.get ())) {
		// TODO: Render map
		// TODO: Render UI (includes text)

		/*
		// Text render code
		std::unique_ptr<SDL_Surface, decltype (&SDL_FreeSurface)> text_surface {TTF_RenderText_Solid (font.get (), "text", BLACK), SDL_FreeSurface};

		if (text_surface) {
			std::unique_ptr<SDL_Texture, decltype (&SDL_DestroyTexture)> text_texture {SDL_CreateTextureFromSurface (renderer.get (), text_surface.get ()), SDL_DestroyTexture};
			std::unique_ptr<SDL_Rect> sprite {new SDL_Rect ()};

			sprite->w = text_surface->w;
			sprite->h = text_surface->h;

			if (text_texture) {
				SDL_RenderCopy (renderer.get (), text_texture.get (), sprite.get (), sprite.get ());
			} else {
				std::cout << "Text texture creation error: " << SDL_GetError () << std::endl;
			}
		} else {
			std::cout << "Text render error: " << TTF_GetError () << std::endl;
		}
		*/

		SDL_RenderPresent (renderer.get ());
	} else {
		std::cout << "Renderer clear error: " << SDL_GetError () << std::endl;
	}
}

void MediaManager::play () {

}
