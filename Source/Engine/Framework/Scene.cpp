#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace viper
{
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		for (auto& actor : _actors) {
			actor->Update(dt); // Draw the actor
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