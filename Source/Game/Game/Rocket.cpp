#include "Rocket.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Player.h"

using namespace std;

void Rocket::Update(float dt)
{
	viper::vec2 force = viper::vec2{ viper::vec2  {1, 0}.Rotate(viper::math::degToRad(transform.rotation)) * thrust * speed };
	velocity += force;

	transform.pos.x = viper::math::wrap(transform.pos.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.pos.y = viper::math::wrap(transform.pos.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());
}

void Rocket::OnCollision(Actor * other)
{
	cout << other->tag << endl;

	}
