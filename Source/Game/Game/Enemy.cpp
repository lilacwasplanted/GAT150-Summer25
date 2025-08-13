#include "Player.h"
#include "Enemy.h"
#include "Math/Transform.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Rocket.h"
#include "GameData.h"
#include "Math/Vector2.h"
#include "Math/Math.h"

void Enemy::Update(float dt)
{
    bool playerSeen = false;

    Player* player = scene->GetActorByName<Player>("player");
    if (player) {
        viper::vec2 direction{ 0, 0 };
        direction = player->transform.pos - transform.pos;

        direction = direction.Normalized();
        viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation));

        float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = viper::vec2::SignedAngleBetween(forward, direction);
            angle = viper::math::sign(angle);
            transform.rotation += viper::math::radToDeg(angle * 5 * dt);
        }
    }

    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation)) * speed;
    velocity += force * dt;

    transform.pos.x = viper::math::wrap(transform.pos.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.pos.y = viper::math::wrap(transform.pos.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    // check fire
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipVerts, viper::vec3{ 0.0f, 1.0f, 0.0f });
        // spawn rocket at player position and rotation
        viper::Transform transform{ this->transform.pos, this->transform.rotation, 2.0f };
        auto rocket = make_unique<Rocket>(transform, model);
        rocket->speed = 500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "enemy";

        scene->AddActor(move(rocket));
    }

    Actor::Update(dt);
}
