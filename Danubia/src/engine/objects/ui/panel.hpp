#pragma once
#ifndef PANEL_HPP
#define PANEL_HPP

#include "ui_object.hpp"

/*
 * UI element that can hold other elements
 * Useful for organising UI, as element position is parent-relative
 */
struct Panel : UIObject {
	std::vector<UIObject> children {};
};

#endif
