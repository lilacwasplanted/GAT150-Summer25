#pragma once
#include "Framework/Actor.h"

class Player : public viper::Actor {
public:
	float speed = 200;
	float rotationRate = 180.f;
	float fireTime = 0.2f;
	float fireTimer = 0;


public:
	Player () = default;
	Player(const viper::Transform& transform, shared_ptr<class viper::Model> model) :
		Actor{ transform, model }

	{}
	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(Actor* other) override;

};