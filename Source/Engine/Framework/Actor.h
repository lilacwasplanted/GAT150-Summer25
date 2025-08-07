#pragma once
#include "Math/Transform.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

#include <memory>
using namespace std;

namespace viper
{
	class Actor {
	public:

				Actor() = default;
				Actor(const Transform& transform,  res_t<Texture> texture) :
					_transform{ transform },
					_texture{texture}
				{	}
				;

				virtual void Update(float dt);
				virtual void Draw(Renderer& renderer);

				void GetRadius();
				Transform& GetTransform() { return _transform; }
	protected:
		res_t<Texture> _texture;
		Transform _transform;
		shared_ptr<Model> _model;
	}; 
}