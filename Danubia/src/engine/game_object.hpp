#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <SDL.h>
#include "texture.hpp"

class GameObject {
public:
    struct RenderRequest {
        Texture* texture;
        SDL_Rect* sprite;
        SDL_Rect* destination;
    };

	GameObject (std::string name, Texture* texture, SDL_Rect* sprites);
	~GameObject ();
    RenderRequest* request_render (unsigned int x, unsigned int y, SDL_Rect* sprite = NULL);
private:
    std::string name;
    Texture* texture;
    // TODO: Turn into a vector
    SDL_Rect* sprites;
};

#endif
