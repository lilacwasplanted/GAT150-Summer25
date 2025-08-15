#include "Player.h"
#include "Engine.h"
#include "Rocket.h"
#include "GameData.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
using namespace std;

void Player::Update(float dt)
{
	float rotate = 0;

	if (INPUT.GetKeyDown(SDL_SCANCODE_A)) rotate = -1; 
	if (INPUT.GetKeyDown(SDL_SCANCODE_D)) rotate = +1; 

	_transform.rotation += (rotate * rotationRate) *dt; 

	//thrust
	float thrust = 0;
	if (INPUT.GetKeyDown(SDL_SCANCODE_W)) thrust = -1; 
	if (INPUT.GetKeyDown(SDL_SCANCODE_S)) thrust = -1; 

	viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::math::degToRad(_transform.rotation)) * thrust * speed;
	velocity += force * dt; 

	_transform.pos.x = viper::math::wrap(_transform.pos.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	_transform.pos.y = viper::math::wrap(_transform.pos.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	//Check fire
	fireTimer -= dt;

	if (INPUT.GetKeyDown(SDL_SCANCODE_SPACE && fireTimer <= 0 )) {
		fireTimer = fireTime;

		shared_ptr<viper::Model> model = make_shared<viper::Model>(GameData::shipVerts, viper::vec3{ 0.0f, 0.4f, 1.0f });
		viper::Transform transform{ this->_transform.pos, this->_transform.pos, 2.0f };
	auto  rocket = make_unique<Rocket>(transform, model);
	rocket->speed = 1500.0f;
	rocket->name = "rocket";
	rocket->tag = "player";

	_scene->AddActor(std::move(rocket));
	}
	//Spawn Rocket at Player position and rotation

	Actor::Update(dt); 


	//if (direction.LengthSqr() > 0) {
	//	direction = direction.Normalized();
	//	_transform.pos += direction * speed * dt; // Update the position based on the direction and speed
	//}
	
}
