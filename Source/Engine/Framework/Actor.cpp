#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper {
	void Actor::Update(float dt)
	{
		//
	}

	void Actor::Draw(Renderer& renderer)
	{
		_model->Draw(renderer, _transform);
	}
};