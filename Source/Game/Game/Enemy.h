#pragma once

#include "Framework/Actor.h"

class Enemy : public viper::Actor {
public:
	Enemy() = default;
	Enemy(const viper::Transform& transform, shared_ptr<class viper::Model> model) :
		Actor{ transform, model }
	{	}

	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(Actor* other) override;

};