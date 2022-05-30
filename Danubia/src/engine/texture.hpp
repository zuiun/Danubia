#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <SDL.h>

class Texture {
public:
    Texture (SDL_Renderer* renderer, std::string path);
    ~Texture ();
    SDL_Texture* get_sheet ();
    unsigned int get_width ();
    unsigned int get_height ();
private:
    SDL_Texture* sheet;
    unsigned int width;
    unsigned int height;
};

#endif
