#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include <rapidjson/document.h>
#include <string>

#define JSON_READ(value, data)				viper::json::Read(value, #data, data)
#define JSON_READ_NAME(value, name, data)	viper::json::Read(value, name, data)

#define JSON_HAS(value, data)				value.HasMember(#data)
#define JSON_GET(value, data)				value[#data]

namespace viper::json {
	using value_t = rapidjson::Value;
	using document_t = rapidjson::Document;

	bool Load(const std::string& filename, document_t& document);

	bool Read(const value_t& value, const std::string& name, bool& data);
	bool Read(const value_t& value, const std::string& name, int& data);
	bool Read(const value_t& value, const std::string& name, float& data);
	bool Read(const value_t& value, const std::string& name, std::string& data);
	bool Read(const value_t& value, const std::string& name, vec2& data);
	bool Read(const value_t& value, const std::string& name, vec3& data);
}
