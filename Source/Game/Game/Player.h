#pragma once
#include "Framework/Component.h"

class Player : public viper::Component {
public:
	float speed;
	float rotationRate;
	float fireTime;
	float fireTimer;

public:
	Player() = default;

	CLASS_PROTOTYPE(Player)

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other);
};
