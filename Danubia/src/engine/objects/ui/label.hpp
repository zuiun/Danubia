#pragma once
#ifndef LABEL_HPP
#define LABEL_HPP

#include <string>
#include "ui_object.hpp"

/*
 * UI element that can display data
 */
struct Label : UIObject {
	std::string text {};
};

#endif
