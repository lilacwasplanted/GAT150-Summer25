#pragma once

namespace viper {
	template <typename T>
	class Singleton {
	public:
		Singleton(const Singleton&) = delete;
		Singleton& operator = (const Singleton&) = delete;

		static T& Instance() {
			static T instance;
			return instance;
		}

	protected:
		Singleton() = default;
	};
}