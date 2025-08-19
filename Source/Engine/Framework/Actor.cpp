#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper {
	void Actor::Update(float dt)
	{
		if (destroyed) return;

	if (lifespan != 0.0f) {
			lifespan -= dt;
			destroyed = lifespan <= 0;
	}
		transform.pos += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	};
	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		_model->Draw(renderer, transform);	
		//renderer.DrawTexture(_texture.get(), _transform.pos.x, _transform.pos.y, _transform.rotation, _transform.scale);
	}

	float Actor::GetRadius()
	{
		return (_model) ? _model->GetRadius() * transform.scale : 0;
	}
	//void Actor::GetRadius() {
	//	return (_texture) ? _texture->GetSize().Length * 0.5f)* transform.scale * 0.0f;
	//}
};