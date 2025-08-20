#pragma once
#include "Framework/Component.h"

class Player : public viper::Component {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

public:
	Player() = default;

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other);
};
