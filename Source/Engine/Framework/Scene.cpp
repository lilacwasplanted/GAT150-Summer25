#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Core/StringHelper.h"

namespace viper
{
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		//update all actors
		for (auto& actor : _actors) {
			actor->Update(dt); // Draw the actor
		}

		for (auto iter = _actors.begin(); iter != _actors.end();) {
			if ((*iter)->destroyed) {
				// If the actor is marked for destruction, remove it from the scene
				iter = _actors.erase(iter);
			}
			else {
				iter++; // Move to the next actor
			}
		}

		//Check for collisions
		for (auto& actorA : _actors) {
			for (auto& actorB : _actors) {
				if (actorA == actorB || actorA->destroyed || actorB->destroyed) continue;

				float distance = (actorA->transform.pos - actorB->transform.pos).Length();
				if (distance <= (actorA->GetRadius() + actorB->GetRadius())) {
					// Collision detected, call OnCollision on both actors
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
				
			}
		}
		

	}



	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : _actors) {
			actor->Draw(renderer); // Draw the actor
		}
	}

	void Scene::AddActor(unique_ptr<class Actor> actor)
	{
		actor->scene = this;
		_actors.push_back(move(actor));
	}

	void Scene::RemoveAllActors()
	{
		_actors.clear();
	}


}