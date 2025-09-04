#pragma once
#include "Core/StringHelper.h"
#include "Core/Singleton.h"
#include "Core/Logger.h"
#include "Resource.h"
#include <string>
#include <map>
#include <iostream>

namespace viper {
	class ResourceManager : public Singleton<ResourceManager> {
	public:
		void Clear() { m_resources.clear(); }

		template<typename T, typename ... Args>
		requires derived_from<T, Resource>
		res_t<T> Get(const string& name, Args&& ... args);

		template<typename T, typename ... Args>
		requires derived_from<T, Resource>
		res_t<T> GetWithID(const string& id, const string& name, Args&& ... args);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

	private:
		 map< string, res_t<Resource>> m_resources;
	};

	template<typename T, typename ... Args>
	requires derived_from<T, Resource>
	inline res_t<T> ResourceManager::Get(const string& name, Args&& ... args) {
		return GetWithID<T>(name, name, forward<Args>(args)...);
	}

	template<typename T, typename ...Args>
	requires derived_from<T, Resource>
	inline res_t<T> ResourceManager::GetWithID(const string& id, const string& name, Args && ...args)	{
		 string key = tolower(id);

		auto iter = m_resources.find(key);
		// check if exists
		if (iter != m_resources.end()) {
			// get value in iterator
			auto base = iter->second;
			// cast to data type T
			auto resource = dynamic_pointer_cast<T>(base);
			// check if cast was successful
			if (resource == nullptr) {
				Logger::Error("Resource type mismatch: {}", key);
				return res_t<T>();
			}

			// return resource
			return resource;
		}

		// load resource
		res_t<T> resource = make_shared<T>();
		if (resource->Load(name, forward<Args>(args)...) == false) {
			Logger::Error("Could not load resource: {}", name);
			return res_t<T>();
		}

		// add resource to resource manager
		m_resources[key] = resource;

		return resource;

	}

	inline ResourceManager& Resources() { return ResourceManager::Instance(); }
}
