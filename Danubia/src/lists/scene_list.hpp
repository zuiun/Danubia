#pragma once
#ifndef SCENE_OBJECTS_HPP
#define SCENE_OBJECTS_HPP

#include <array>
#include "../engine/scene.hpp"

namespace scene_objects {
	struct SceneData {
		enum Type {
			MENU,
			GAMEPLAY
		};

		Type type;
	};
	enum Scenes {
		MENU
	};

	// TODO: Eventually make these into files
	std::array<SceneData, 10> const scenes {
		// MENU
		{SceneData::Type::MENU}
	};
}

#endif
