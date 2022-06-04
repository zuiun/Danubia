#include "game_object.hpp"

GameObject::GameObject (std::string path) {
	this->sprite_sheets = nullptr;
	this->sheet = 0;
	this->sprite = 0;
	this->frame_buffer = BUFFER;
	this->is_visible = true;
}

GameObject::~GameObject () {
	for (SpriteSheet* i : *sprite_sheets) {
		SDL_DestroyTexture (i->texture);
		i->texture = nullptr;
	}
}

GameObject::RenderInformation* GameObject::create_render_information () {
	RenderInformation* result = new RenderInformation ();
	SpriteSheet* sprite_sheet = sprite_sheets->at (sheet);

	result->texture = sprite_sheet->texture;
	result->sprite = sprite_sheet->sprites->at (sprite);
	return result;
}

void GameObject::animate () {
	if (frame_buffer > 0) {
		frame_buffer--;
	} else {
		frame_buffer = BUFFER;
		sprite = (sprite + 1) % sprite_sheets->at (sheet)->sprites->size ();
	}
}
