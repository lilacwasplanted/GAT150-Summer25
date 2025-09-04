#include "Mesh.h"
#include "Renderer.h"

namespace viper {
	bool Mesh::Load(const string& filename) {

		 string buffer;
		if (!file::ReadTextFile(filename, buffer)) {
			Logger::Error("Could not read file: {}", filename);
			return false;
		}

		 stringstream stream(buffer);

		// read color
		stream >> m_color;

		// read points
		vec2 point;
		while (stream >> point) {
			m_points.push_back(point);
		}

		if (!stream.eof()) {
			Logger::Error("Could not parse file: {}", filename);
			return false;
		}

		return true;
	}

	/// <summary>
	/// Draws the model by rendering lines between its points using the specified renderer.
	/// </summary>
	/// <param name="renderer">The Renderer object used to draw the model.</param>
	void Mesh::Draw(class Renderer& renderer, const vec2& position, float rotation, float scale) {
		if (m_points.empty()) return;

		renderer.SetColor(m_color.r, m_color.g, m_color.b);
		// iterate through all points, draw line
		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 p1 = (m_points[i].Rotate(math::degToRad(rotation)) * scale) + position;
			vec2 p2 = (m_points[i + 1].Rotate(math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	/// <summary>
	/// Draws the model using the specified renderer and transformation.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the model.</param>
	/// <param name="transform">The transformation to apply, including position, rotation, and scale.</param>
	void Mesh::Draw(Renderer& renderer, const Transform& transform) {
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	/// <summary>
	/// Calculates and updates the model's radius as the maximum distance from the origin among all points.
	/// </summary>
	void Mesh::CalculateRadius()
	{
		m_radius = 0;
		for (auto& point : m_points) {
			float length = point.Length();
			if (length > m_radius) m_radius = length;
		}
	}
}