#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "ui_object.hpp"

/*
 * UI element that can accept user input
 */
struct Button : UIObject {
	bool is_toggled {false};
};

#endif
