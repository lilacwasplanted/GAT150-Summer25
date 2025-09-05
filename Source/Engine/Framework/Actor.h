#pragma once
#include "Object.h"
#include "Component.h"
#include "Renderer/Texture.h"
#include "Math/Transform.h"
#include <string>
#include <memory>
#include <vector>

using namespace std;

namespace viper {
	class Actor : public Object {
	public:
		string tag;

		bool persistent{ false };
		bool destroyed{ false };
		float lifespan{ 0 };

		Transform transform;
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);



		CLASS_PROTOTYPE(Actor)

		void Read(const json::value_t& value) override;

		virtual void Start();
		virtual void Destroyed();
		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) {}

		// components
		void AddComponent(unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		vector<T*> GetComponents();


	protected:
		vector<unique_ptr<Component>> _components;
	};


	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : _components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline vector<T*> Actor::GetComponents()
	{
		vector<T*> results;

		for (auto& component : _components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				results.push_back(result);
			}
		}

		return results;
	}
}
