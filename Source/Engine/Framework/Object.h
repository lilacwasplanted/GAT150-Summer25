#pragma once
#include "Core/Serializable.h"
#include <string>
using namespace std;

#define CLASS_PROTOTYPE(classname) virtual unique_ptr<Object> Clone() {return make_unique<classname>(*this);}

namespace viper {
	class Object : public Serializable {
	public:
		string name;
		bool active{ true };

	public:
		Object() = default;
		virtual ~Object() = default;

		virtual unique_ptr<Object> Clone() = 0;

		void Read(const json::value_t& value) override;
	};
}