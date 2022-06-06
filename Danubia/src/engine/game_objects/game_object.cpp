#include "game_object.hpp"

GameObject::GameObject (std::string path) {
	// TODO: Import sprites from path
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
