#include "../GamePCH.h"
#include "Player.h"
#include "Rocket.h"
#include "SpaceGame.h"
#include "GameData.h"

FACTORY_REGISTER(Player)

void Player::Read(const viper::json::value_t& value)
{ 
    viper::Object::Read(value);
}

void Player::Update(float dt)
{
  
  viper::Particle particle;
  particle.position = owner->transform.position;
  particle.velocity = viper::vec2{ viper::random::getReal(-200.0f, 200.0f), viper::random::getReal(-200.0f, 200.0f) };
  particle.color = viper::vec3{ 1, 1, 1 };
  particle.lifespan = 2;
  //viper::GetEngine().GetPS().AddParticle(particle);

  // rotation
  float rotate = 0;
  if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
  if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

  owner->transform.rotation += (rotate * rotationRate) * dt;

  // thrust
  float thrust = 0;
  if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
  if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

  viper::vec2 direction{ 1, 0 };
  viper::vec2 force = direction.Rotate(viper::math::degToRad(owner->transform.rotation)) * thrust * speed;
  //velocity += force * dt;
  auto* rb = owner->GetComponent<viper::RigidBody>();
  if (rb) {
    rb->velocity += force * dt;
  }

  owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
  owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());
  
  /*
  // check fire key pressed
  fireTimer -= dt;
  if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
    fireTimer = fireTime;

    //viper::GetEngine().GetAudio().PlaySound("clap");
    auto sound = viper::Resources().Get<viper::AudioClip>("bass.wav", viper::GetEngine().GetAudio()).get();
    if (sound) {
      viper::GetEngine().GetAudio().PlaySound(*sound);
    }

    // spawn rocket at player position and rotation
    viper::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
    auto rocket = make_unique<Rocket>(transform);
    rocket->speed = 1500.0f;
    rocket->lifespan = 1.5f;
    rocket->name = "rocket";
    rocket->tag = "player";

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

void Player::OnCollision(viper::Actor* other)
{
  if (owner->tag != other->tag) {
    owner->destroyed = true;
    dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
  }
}



