#pragma once
#include "Json.h"

namespace viper {
	class Serializable {
	public:
		virtual ~Serializable() = default;

		virtual void Read(const json::value_t& value) = 0;
	};
}