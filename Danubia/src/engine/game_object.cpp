#include "game_object.hpp"

GameObject::GameObject (std::string name, Texture* texture, SDL_Rect* sprites) {
	this->name = name;
	this->texture = texture;
	this->sprites = sprites;
}

GameObject::~GameObject () {
	// TODO: Free everything
}

GameObject::RenderRequest* GameObject::request_render (unsigned int x, unsigned int y, SDL_Rect* sprite) {
	GameObject::RenderRequest* result = new GameObject::RenderRequest ();

	result->texture = texture;
	result->sprite = sprite;
	result->destination = new SDL_Rect ();
	result->destination->x = x;
	result->destination->y = y;
	result->destination->w = sprite ? sprite->w : texture->get_width ();
	result->destination->h = sprite ? sprite->h : texture->get_height ();
	return result;
}
