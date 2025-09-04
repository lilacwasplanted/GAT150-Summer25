#pragma once
#include "Framework/Component.h"

class Enemy : public viper::Component {
public:
	float speed;
	float fireTimer;
	float fireTime;

public:
	Enemy() = default;

	CLASS_PROTOTYPE(Enemy)

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other);
};
