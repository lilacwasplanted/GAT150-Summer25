#pragma once
#include "Object.h"

namespace viper {
	class Component : public Object {
	public:
		class Actor* owner{ nullptr };

	public:
		Component() = default;

		virtual void Start() {}
		virtual void Destroyed() {}

		virtual void Update(float dt) = 0;

		//void Read(const viper::json::value_t& value) override;
	};
}
