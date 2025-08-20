#pragma once
#include "Core/StringHelper.h"
#include "Core/Serializable.h"
#include <string>
#include <vector>
#include <list>
#include <memory>

namespace viper {
	class Actor;
	class Game;

	class Scene : public Serializable {
	public:
		Scene(Game* game) : m_game{ game } {}

		void Read(const json::value_t& value) override;

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		Game* m_game{ nullptr };
		std::list<std::unique_ptr<Actor>> m_actors;

	};

	/// <summary>
	/// Retrieves an actor from the scene by name and casts it to the specified type.
	/// </summary>
	/// <typeparam name="T">The type to which the found actor should be cast.</typeparam>
	/// <param name="name">The name of the actor to search for (case-insensitive).</param>
	/// <returns>A pointer to the actor cast to type T if found and the cast is successful; otherwise, nullptr.</returns>
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors) {
			if (viper::tolower(actor->name) == viper::tolower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					return object;
				}
			}
		}

		return nullptr;
	}

	/// <summary>
	/// Retrieves all actors in the scene with a tag matching the specified value and of the specified type.
	/// </summary>
	/// <typeparam name="T">The type to which actors should be cast. Only actors of this type are included in the results.</typeparam>
	/// <param name="tag">The tag to match against each actor's tag (case-insensitive).</param>
	/// <returns>A vector of pointers to actors of type T whose tag matches the specified tag.</returns>
	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		for (auto& actor : m_actors) {
			if (viper::tolower(actor->tag) == viper::tolower(tag)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}

		return results;
	}
}