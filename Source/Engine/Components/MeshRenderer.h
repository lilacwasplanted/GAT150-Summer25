#pragma once
#include "RendererComponent.h"

namespace viper {
	class MeshRenderer : public RendererComponent {
	public:
		 string meshName;

		 CLASS_PROTOTYPE(MeshRenderer)

	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;
	};
}


