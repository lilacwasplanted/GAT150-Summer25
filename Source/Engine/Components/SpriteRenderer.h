#pragma once
#include "RendererComponent.h"

using namespace std;

namespace viper {
	class SpriteRenderer : public RendererComponent {
	public:
		 string textureName;
		 CLASS_PROTOTYPE(SpriteRenderer)

	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};
}


