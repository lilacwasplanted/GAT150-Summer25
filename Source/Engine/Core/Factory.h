#pragma once
#include "Framework/Object.h"
#include "Framework/Actor.h"
#include "StringHelper.h"
#include "Singleton.h"
#include "Logger.h"
#include <map>
#include <memory>
#include <string>

using namespace std;

#define FACTORY_REGISTER(classname) \
class Register##classname {     \
public:               \
	Register##classname() {     \
		viper::Factory::Instance().Register<classname>(#classname); \
	}                \
};                 \
Register##classname register_instance;

namespace viper {
	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;
		virtual unique_ptr<Object> Create() = 0;
	};

	template <typename T>
	requires derived_from<T, Object>
	class Creator : public CreatorBase {
	public:
		unique_ptr<Object> Create() override {
			return make_unique<T>();
		}
	};

	template <typename T>
	requires derived_from<T, Object>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(unique_ptr<T> proto) : 
			_prototype{ move(proto) }
		{ }
		unique_ptr<Object> Create() override {
			return make_unique<T>();
		}
	private:
		unique_ptr<T> _prototype;
	};

	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
		requires derived_from<T, Object>
		void Register(const string& name);

		template<typename T>
		requires derived_from<T, Object>
		void RegisterProto(const string& name, unique_ptr<T> proto);

		template<typename T = Object>
		requires derived_from<T, Object>
		unique_ptr<T> Create(const string& name);

	private:
		map< string, unique_ptr<CreatorBase>> _registry;
	};

	template<typename T>
	requires derived_from<T, Object>
	inline void Factory::Register(const string& name) {
		// make case-insensitive (lowercase)
		string key = tolower(name);
		// add creator to registry
		_registry[key] = make_unique<Creator<T>>();

		Logger::Info("{} added to factory.", name);
	}

	template<typename T>
	requires derived_from<T, Object>
	inline void Factory::RegisterProto(const string& name, unique_ptr<T> proto)
	{
		// make case-insensitive (lowercase)
		string key = tolower(name);
		// add prototype creator to registry
		_registry[key] = make_unique<PrototypeCreator<T>>(move(proto));

		Logger::Info("{} prototype added to factory.", name);
	}

	template<typename T>
	requires derived_from<T, Object>
	inline unique_ptr<T> Factory::Create(const string& name) {
		// make case-insensitive (lowercase)
		string key = tolower(name);

		// look for creator in registry
		auto it = _registry.find(key);
		if (it != _registry.end()) {
			// found creator, create object
			auto object = it->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) {
				object.release();
				return unique_ptr<T>(derived);
			}
			Logger::Error("Type mismatch of factory object: {}", name);
		}
		else {
			Logger::Error("Could not create factory object: {}", name);
		}

		return nullptr;
	}
	template<typename T = Actor>
	requires derived_from<T, Actor>
	unique_ptr<T> Instantiate(const string& name) {
		return Factory::Instance().Create<T>(name);
	}

	template<typename T = Actor>
	requires derived_from<T, Actor>
	unique_ptr<T> Instantiate(const string& name, const vec2& position, float rotation, float scale) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->transform = Transform{ position, rotation, scale };
		return instance;
	}

	template<typename T = Actor>
	requires derived_from<T, Actor>
	unique_ptr<T> Instantiate(const string& name, const Transform& transform) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->transform = transform;
		return instance;
	}
}