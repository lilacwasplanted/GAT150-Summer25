#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
  /*
  bool playerSeen = false;

  Actor* player = owner->scene->GetActorByName<Actor>("player");
  if (player) {
    viper::vec2 direction{ 0, 0 };
    direction = player->transform.position - owner->transform.position;

    direction = direction.Normalized();
    viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation));

    float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
    playerSeen = angle <= 30;

    if (playerSeen) {
      float angle = viper::vec2::SignedAngleBetween(forward, direction);
      angle = viper::math::sign(angle);
      owner->transform.rotation += viper::math::radToDeg(angle * 5 * dt);
    }
  }

  viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;
  //velocity += force * dt;
  //GetComponent<viper::RigidBody>()->velocity += force * dt;

  auto* rb = owner->GetComponent<viper::RigidBody>();
  if (rb) {
    rb->velocity += force * dt;
  }

  owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
  owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

  // check fire
  fireTimer -= dt;
  if (fireTimer <= 0 && playerSeen) {
    fireTimer = fireTime;

    // shared_ptr<viper::Model> model = make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0.0f, 1.0f, 0.0f });
    // spawn rocket at player position and rotation
    viper::Transform transform{ owner->transform.position, owner->transform.rotation, 2.0f };
    auto rocket = make_unique<Actor>(transform);// , viper::Resources().Get<viper::Texture>("textures/blue_01.png", viper::GetEngine().GetRenderer()));
    rocket->speed = 500.0f;
    rocket->lifespan = 1.5f;
    rocket->name = "rocket";
    rocket->tag = "enemy";

    // components
    auto spriteRenderer = make_unique<viper::SpriteRenderer>();
    spriteRenderer->textureName = "textures/missile-2.png";
    rocket->AddComponent( move(spriteRenderer));

    auto rb = make_unique<viper::RigidBody>();
    rocket->AddComponent( move(rb));

    auto collider = make_unique<viper::CircleCollider2D>();
    collider->radius = 10;
    rocket->AddComponent( move(collider));

    scene->AddActor( move(rocket));
  }

  Actor::Update(dt);
  */
}

void Enemy::OnCollision(viper::Actor* other)
{
  if (owner->tag != other->tag) {
    owner->destroyed = true;
    owner->scene->GetGame()->AddPoints(100);
    for (int i = 0; i < 100; i++) {
      viper::Particle particle;
      particle.position = owner->transform.position;
      particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
      particle.color = viper::vec3{ 1, 1, 1 };
      particle.lifespan = 2;

      viper::GetEngine().GetPS().AddParticle(particle);
    }
  }
}
