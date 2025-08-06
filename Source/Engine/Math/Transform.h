#pragma once
#include "Vector2.h"

namespace viper {
	struct Transform {
		vec2 pos { 0, 0 };
		float rotation = 0;
		float scale = 1;

		Transform() = default;
		Transform(const vec2& position, float rotation = 0, float scale = 1) :
			pos{ position },
			rotation{ rotation },
			scale{ scale }
			{}


	};
}