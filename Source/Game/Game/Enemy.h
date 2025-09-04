#pragma once
#include "Framework/Component.h"

class Enemy : public viper::Component {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

public:
	Enemy() = default;

	CLASS_PROTOTYPE(Enemy)

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other);
};
