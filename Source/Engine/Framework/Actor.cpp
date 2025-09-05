#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"

using namespace std;
namespace viper {
	FACTORY_REGISTER(Actor)

	Actor::Actor(const Actor& other):
		Object{ other },
		tag{ other.tag },
		lifespan{ other.lifespan },
		transform{ other.transform }
	{
		for (auto& component : other._components) {
			auto clone = unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(move(clone));
		}
	}
	void Actor::Start()
	{
		for (auto& component : _components) {
			component->Start();
		}
	}
	void Actor::Destroyed()
	{
		for (auto& component : _components) {
			component->Destroyed();
		}
	}
	void Actor::Update(float dt)
	{
		if (destroyed) return;
		
		if (lifespan > 0) {
			lifespan -= dt;
			if (lifespan <= 0) {
				destroyed = true;
				return;
			}
		}

		// update all components
		for (auto& component : _components) {
			if (component->active) component->Update(dt);
		}
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		for (auto& component : _components) {
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->Draw(renderer);
				}
			}
		}
	}

	void Actor::AddComponent(unique_ptr<Component> component)
	{
		component->owner = this;
		_components.push_back(move(component));
	}


	void Actor::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);
		JSON_READ(value, persistent);

		if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

		//read components
		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {

				string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);

				AddComponent(move(component));

			}
		}
	}

}
