#pragma once
#include "Math/Transform.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include <memory>
using namespace std;

namespace viper
{
	class Actor {
	public:
				Actor() = default;
				Actor(const Transform& transform,  shared_ptr<class Model> model) :
					_transform{ transform },
					_model{ model }
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