#include "Player.h"
#include "Engine.h"
#include "Rocket.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Core/Random.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"
using namespace std;

void Player::Update(float dt)
{
	viper::Particle particle;
	particle.pos = transform.pos;
	particle.velocity = viper::vec2{ viper::random::getReal(-200.0f, 200.0f), viper::random::getReal(-200.0f, 200.0f) };
	particle.color = viper::vec3{ 1,1,1 };
	particle.lifespan = 2;
	viper::GetEngine().GetParticle().AddParticle(particle);
	


	float rotate = 0;

	if (INPUT.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (INPUT.GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

	transform.rotation += (rotate * rotationRate) * dt;

	//thrust
	float thrust = 0;
	if (INPUT.GetKeyDown(SDL_SCANCODE_W)) thrust = -1;
	if (INPUT.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::math::degToRad(transform.rotation)) * thrust * speed;
	velocity += force * dt;

	transform.pos.x = viper::math::wrap(transform.pos.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.pos.y = viper::math::wrap(transform.pos.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	//Check fire
	fireTimer -= dt;
	if (INPUT.GetKeyDown(SDL_SCANCODE_SPACE && fireTimer <= 0)) {
		fireTimer = fireTime;

		viper::GetEngine().GetAudio().PlaySound("clap");

		shared_ptr<viper::Model> model = make_shared<viper::Model>(GameData::shipVerts, viper::vec3{ 0.0f, 0.4f, 1.0f });
		viper::Transform transform{ this->transform.pos, this->transform.rotation, 2.0f };
		auto  rocket = make_unique<Rocket>(transform, model);
		rocket->speed = 1500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "player";

		scene->AddActor(move(rocket));
	}
	//Spawn Rocket at Player position and rotation

	Actor::Update(dt);


	//if (direction.LengthSqr() > 0) {
	//	direction = direction.Normalized();
	//	_transform.pos += direction * speed * dt; // Update the position based on the direction and speed
	//}

}

void Player::OnCollision(Actor* other)
{
	if (tag != other->tag)
	{
		destroyed = true;
		dynamic_cast<SpaceGame*> (scene->GetGame())->OnPlayerDeath();
	}
}
