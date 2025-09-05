#pragma once
#include "RendererComponent.h"

using namespace std;

namespace viper {
	class SpriteRenderer : public RendererComponent {
	public:
		res_t<Texture> texture;
		 string textureName;
		 CLASS_PROTOTYPE(SpriteRenderer)

	public:
		virtual void Start() override;

		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};
}


