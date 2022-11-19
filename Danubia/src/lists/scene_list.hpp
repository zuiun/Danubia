#pragma once
#ifndef SCENE_OBJECTS_HPP
#define SCENE_OBJECTS_HPP

#include <vector>

namespace scene_objects {
	struct SceneData {
		enum Type {
			MENU,
			GAMEPLAY
		};

		Type type {Type::MENU};
		std::vector<std::vector<Tile>> map {};
	};
	enum Scenes {
		MENU
	};

	std::array<SceneData, 10> const scenes {
		// MENU
		{SceneData::Type::MENU}
	};
}

#endif
