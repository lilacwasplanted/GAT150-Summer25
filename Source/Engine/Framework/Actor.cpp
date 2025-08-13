#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper {
	void Actor::Update(float dt)
	{
		_transform.pos += velocity * dt;
	}

	void Actor::Draw(Renderer& renderer)
	{
		_model->Draw(renderer, _transform);	
		//renderer.DrawTexture(_texture.get(), _transform.pos.x, _transform.pos.y, _transform.rotation, _transform.scale);
	}
	//void Actor::GetRadius() {
	//	return (_texture) ? _texture->GetSize().Length * 0.5f)* transform.scale * 0.0f;
	//}
};