#include "game_object.hpp"

GameObject::GameObject (std::string path) :
	sprite_sheets {},
	sheet {},
	sprite {},
	frame_buffer {BUFFER},
	is_visible {true} {
}

GameObject::RenderInformation GameObject::create_render_information () {
	return RenderInformation {sprite_sheets.at (sheet), sheet};
}

void GameObject::animate () {
	if (frame_buffer > 0) {
		frame_buffer--;
	} else {
		frame_buffer = BUFFER;
		sprite = (sprite + 1) % sprite_sheets.at (sheet).sprites.size ();
	}
}
