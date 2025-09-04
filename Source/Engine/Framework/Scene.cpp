#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Components/ColliderComponent.h"
using namespace std;

namespace viper {
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		// update all actors
		for (auto& actor : _actors) {
			if (actor->active) {
				actor->Update(dt);
			}
		}

		// remove destroyed actors
		for (auto iter = _actors.begin(); iter != _actors.end(); ) {
			if ((*iter)->destroyed) {
				iter = _actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		// check for collisions
		for (auto& actorA : _actors) {
			for (auto& actorB : _actors) {
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				// make sure both actors have a collider
				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
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
			if (actor->active) {
				actor->Draw(renderer);
			}
		}
	}

	/// <summary>
	/// Adds an actor to the scene by transferring ownership of the actor.
	/// </summary>
	/// <param name="actor">A unique pointer to the actor to be added. Ownership of the actor is transferred to the scene.</param>
	void Scene::AddActor(unique_ptr<Actor> actor) {
		actor->scene = this;
		_actors.push_back( move(actor));
	}

	void Scene::RemoveAllActors(bool force) {
		// remove destroyed actors
		for (auto iter = _actors.begin(); iter != _actors.end(); ) {
			if (!(*iter)->persistent || force) {
				iter = _actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	void Scene::Read(const json::value_t& value) {
		//read prototypes
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {

				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);
				string name = actor->name;
				Factory::Instance().RegisterProto<Actor>(name, move(actor));

			}
		}

		//read actors
		if (JSON_HAS(value, actor)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {

				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(move(actor));
			}
		}
	}
}