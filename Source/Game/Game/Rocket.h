#pragma once
#include "Framework/Actor.h"
#include "Renderer/Texture.h"       


using namespace std;

class Rocket : public viper::Actor {
public:
	float speed = 200;

	Rocket() = default;
	Rocket(const viper::Transform& transform, res_t<viper::Texture> texture) :
		viper::Actor(transform, texture) {}

};