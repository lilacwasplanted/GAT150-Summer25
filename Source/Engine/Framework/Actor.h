#pragma once
#include "Math/Transform.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

#include <string>
#include <memory>
using namespace std;

namespace viper
{
	class Actor {
	public:
		string name;
		string tag;

		vec2 velocity{ 0,0 };
		float damping{ 0.0f };

		bool destroyed{ false };
		float lifespan{ 0.0f };

		Transform transform;
		class Scene* scene = nullptr;

	public:
				Actor() = default;
				Actor(const Transform& transform,  shared_ptr<class Model> model) :
					transform{ transform },
					_model{model}
				{	}
				;

				virtual void Update(float dt);
				virtual void Draw(Renderer& renderer);

				virtual void OnCollision(Actor* other) = 0;

				float GetRadius();
	protected:
		shared_ptr<Model> _model;
	}; 
}