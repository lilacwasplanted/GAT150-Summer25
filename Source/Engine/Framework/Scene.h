#pragma once
#include "../Core/StringHelper.h"
#include <list>
#include <vector>
#include <memory>
#include <string>

using namespace std;
class Actor;
class Game;

namespace viper{
	class Scene {
	public: 
		Scene(Game* game) : _game{ game } { }

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(unique_ptr<Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
	T* GetActorByName(const string& name);

		template<typename T = Actor>
		 vector<T*> GetActorsByTag(const string& tag);

		 Game* GetGame() const { return _game; }

	private:
		Game* _game{ nullptr };
		list<unique_ptr<class Actor>> _actors;
	};
	/// <summary>
	/// Finds and returns a pointer to an actor with the specified name, performing a case-insensitive comparison.
	/// </summary>
	/// <typeparam name="T">The type of actor to search for. Defaults to Actor.</typeparam>
	/// <param name="name">The name of the actor to search for.</param>
	/// <returns>A pointer to the actor with the specified name if found; otherwise, nullptr.</returns>
	template<typename T = Actor>
	T* GetActorByName(const string& name) {
		for (auto& actor : _actors) {
			if (tolower(actor->name) == tolower(name)) {
				return actor.get();
			}
		}
		return nullptr;
		}

		/// <summary>
		/// Retrieves all actors with a specified tag, cast to the given type.
		/// </summary>
		/// <typeparam name="T">The type to cast the actors to. Defaults to Actor.</typeparam>
		/// <param name="tag">The tag to search for among the actors.</param>
		/// <returns>A vector containing pointers to actors of type T that have the specified tag.</returns>
		template<typename T = Actor>
		vector<T*> GetActorsByTag(const string& tag) {
			vector<T*> results;
			for(auto& actor : _actors) {
				if (tolower(actor->) == tolower(tag)) {
					T* object = dynamic_cast<T*>(actor);
					if (object) {
						results.push_back(object);
					}
				}
			}
			return results;
		}

}