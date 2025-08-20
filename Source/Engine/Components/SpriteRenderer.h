#pragma once
#include "RendererComponent.h"

namespace viper {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};
}


