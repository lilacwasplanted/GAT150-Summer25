#pragma once
#include "../Core/StringHelper.h"
#include <list>
#include <vector>
#include <memory>
#include <string>


using namespace std;


namespace viper{
	class Scene {
	public: 
		Scene() = default;

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(unique_ptr<class Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
	T* GetActorByName(const string& name);

		template<typename T = Actor>
		 vector<T*> GetActorsByTag(const string& tag);
	private:
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
			if (viper::tolower(actor->name) == viper::tolower(name)) {
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
				if (viper::tolower(actor->) == viper::tolower(tag)) {
					T* object = dynamic_cast<T*>(actor);
					if (object) {
						results.push_back(object);
					}
				}
			}
			return results;
		}

}