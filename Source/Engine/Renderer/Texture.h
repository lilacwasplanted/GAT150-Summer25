#pragma once
#include "Math/Vector2.h"
#include <string>
#include <SDL3/SDL.h>

using namespace std;
namespace viper {
	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const string& filename, class Renderer& renderer);

		viper::vec2 GetSize();

		friend class Renderer;

	private:
		struct SDL_Texture* _texture{ nullptr };
	};
}