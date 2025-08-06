#pragma once
#include "Framework/Actor.h"

class Player : public viper::Actor {
public:
	Player () = default;
	Player(const viper::Transform& transform, shared_ptr<class viper::Model> model) :
		Actor{ transform, model }

	{}
	void Update(float dt) override;
private:

};