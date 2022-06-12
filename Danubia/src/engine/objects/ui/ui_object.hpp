#pragma once
#ifndef UI_OBJECT_HPP
#define UI_OBJECT_HPP

#include <memory>
#include <vector>
#include <SDL.h>
#include "../object.hpp"

/*
 * Generic UI element
 */
struct UIObject : Object {
	// Relative to parent
	int x {};
	// Relative to parent
	int y {};
};

#endif
