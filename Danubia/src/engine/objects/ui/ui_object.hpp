#pragma once
#ifndef UI_OBJECT_HPP
#define UI_OBJECT_HPP

#include <SDL.h>
#include "../object.hpp"

/*
 * Generic UI element
 */
struct UIObject : Object {
	SDL_Rect area {};
	// Relative to parent
	int x {};
	// Relative to parent
	int y {};
};

#endif
