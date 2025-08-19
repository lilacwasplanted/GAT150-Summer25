#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "Rocket.h"
#include "GameData.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "Framework/Game.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"

using namespace std;


void Enemy::Update(float dt)
{
	bool playerSeen = false;

	Player* player = scene->GetActorByName<Player>("player");
	if (player) {
		viper::vec2 direction{ 0, 0 };
		direction = player->transform.pos - transform.pos;

		direction = direction.Normalized();
		viper::vec2 foward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation));

		float angle = viper::math::radToDeg(viper::vec2::AngleBetween(foward, direction));
		playerSeen = angle <= 30;

		if (playerSeen){
			float angle = viper::vec2::SignedAngleBetween(foward, direction);
			angle = viper::math::sign(angle);
			transform.rotation += viper::math::radToDeg(angle * 10 * dt);
		}
	}
	viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation)) * speed;
	velocity += force * dt;

	transform.pos.x = viper::math::wrap(transform.pos.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.pos.y = viper::math::wrap(transform.pos.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	//Check fire
	fireTimer -= dt;
	if (fireTimer <= 0 && playerSeen) {
		fireTimer = fireTime;

		shared_ptr<viper::Model> model = make_shared<viper::Model>(GameData::shipVerts, viper::vec3{ 1.0f, 1.0f, 1.0f });
		viper::Transform transform{ this->transform.pos, this->transform.rotation, 2.0f };
		auto  rocket = make_unique<Rocket>(transform, model);
		rocket->speed = 1500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "enemy";

	}
	Actor::Update(dt);
}
	void Enemy::OnCollision(Actor * other) {
		if (tag != other->tag)
		{
			destroyed = true;
			scene->GetGame()->AddPoints(100);
			for (int i = 0; i < 100; i++) {
				viper::Particle particle;
				particle.pos = transform.pos;
				particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
				particle.color = viper::vec3{ 1,1,1 };
				particle.lifespan = 2;

				viper::GetEngine().GetParticle().AddParticle(particle);
			}
		}
	}
