#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Player.h"

using namespace std;


void Enemy::Update(float dt)
{
    Player* player = scene->GetActorByName<Player>("player");
    if (player) {
        viper::vec2 direction{ 0, 0 };
        direction = player->transform.pos - transform.pos;
        direction = direction.Normalized();
		transform.rotation = viper::math::radToDeg(direction.Angle());
    }
    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation)) * speed;
    velocity += force * dt;

    transform.pos.x = viper::math::wrap(transform.pos.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.pos.y = viper::math::wrap(transform.pos.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    Actor::Update(dt);
}
