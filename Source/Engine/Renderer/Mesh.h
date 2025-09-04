#pragma once
#include "Resources/Resource.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include <vector>

namespace viper {
	class Mesh : public Resource {
	public:
		Mesh() = default;
		Mesh(const vector<vec2> points, const vec3& color) :
			m_points{ points },
			m_color{ color }
		{
			CalculateRadius();
		}

		bool Load(const string& filename);

		void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() const { return m_radius; }

	private:
		void CalculateRadius();

	private:
		float m_radius{ 0 };
		 vector<vec2> m_points;
		vec3 m_color{ 1, 1, 1 };
	};
}