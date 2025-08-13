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

	public:
				Actor() = default;
				Actor(const Transform& transform,  shared_ptr<class Model> model) :
					_transform{ transform },
					_model{model}
				{	}
				;

				virtual void Update(float dt);
				virtual void Draw(Renderer& renderer);

				Transform& GetTransform() { return _transform; }
	protected:
		Transform _transform;
		shared_ptr<Model> _model;
	}; 
}