#pragma once
#include "ColliderComponent.h"

namespace viper {
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius{ 0 };

	public:
		void Update(float dt) override;
		bool CheckCollision(ColliderComponent& other) override;
	};
}