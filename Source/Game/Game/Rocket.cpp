#include "Rocket.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include "Player.h"

using namespace std;

void Rocket::Update(float dt)
{
	viper::vec2 force = viper::vec2{ viper::vec2  {1, 0}.Rotate(viper::math::degToRad(transform.rotation)) * speed };
	velocity += force;

	transform.pos.x = viper::math::wrap(transform.pos.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.pos.y = viper::math::wrap(transform.pos.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	float angle = transform.rotation + viper::random::getReal(-60.0f, 60.0f);
	viper::vec2 velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation));
	velocity *= viper::random::getReal(80.0f, 150.0f);

	viper::Particle particle;
	particle.pos = transform.pos;
	particle.velocity = viper::vec2{ viper::random::onUnitCircle() * viper::random::getReal(20.0f, 120.0f) };
	particle.color = (tag == "enemy") ? viper::vec3{ 0, 1, 1 } : viper::vec3{ 1, 1, 0 };
	particle.lifespan = viper::random::getReal(0.15f, 0.3f);

	viper::GetEngine().GetParticle().AddParticle(particle);

	Actor::Update(dt);
}

void Rocket::OnCollision(Actor * other)
{
	if (tag != other->tag)
	{
		destroyed = true;
	}

	}
