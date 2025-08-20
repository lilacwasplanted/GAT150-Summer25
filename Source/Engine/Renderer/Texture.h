#pragma once
#include "Resources/Resource.h"
#include "Math/Vector2.h"
#include <string>

struct SDL_Texture;

namespace viper {
	class Texture : public Resource {
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};
}
