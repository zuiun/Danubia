#pragma once
#ifndef SCENE_LIST_HPP
#define SCENE_LIST_HPP

#include <array>
#include "scene.hpp"

struct SceneData {
	Scene::Type type;
};
enum Scenes {
	MENU
};

std::array<SceneData, 10> const scenes {
	// MENU
	{Scene::Type::MENU}
};

#endif
