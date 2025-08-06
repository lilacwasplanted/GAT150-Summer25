#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
using namespace std;

void Player::Update(float dt)
{

	float speed = 200.0f;

	viper::vec2 direction{ 0, 0 };
	if (INPUT.GetKeyDown(SDL_SCANCODE_W))direction.y = -1; // speed * time.GetDeltaTime();
	if (INPUT.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1; // speed * time.GetDeltaTime();
	if (INPUT.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1; // speed * time.GetDeltaTime();
	if (INPUT.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1; // speed * time.GetDeltaTime();

	if (direction.LengthSqr() > 0) {
		direction = direction.Normalized();
		_transform.pos += direction * speed * dt; // Update the position based on the direction and speed
	}
	
}
