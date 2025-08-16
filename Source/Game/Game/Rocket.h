#pragma once
#include "Framework/Actor.h"


using namespace std;

class Rocket : public viper::Actor {
public:
	float speed = 200;

	Rocket() = default;
	Rocket(const viper::Transform& transform, shared_ptr<viper::Model> model) :
		viper::Actor(transform, model) {}

	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(Actor* other) override;
};