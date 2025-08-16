#include "Model.h"
#include "Renderer.h"

namespace viper {
	/// <summary>
	/// Model by rendering lines between its points using the specified renderer. 
	/// </summary>
	/// <param name="renderer">The Renderer object used to draw the model.</param>
	void Model::Draw(class Renderer& renderer, const vec2& position, float rotation,  float scale) {
		if (_verts.empty()) return;

		renderer.SetColor(_color.r, _color.g, _color.b);
		//iterate the all the points, draw line;
		for (int i = 0; i < _verts.size() - 1; i++)
		{
			vec2 p1 = (_verts[i].Rotate(math::degToRad(rotation)) * scale) + position;
			vec2 p2 = (_verts[i + 1].Rotate(math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	/// <summary>
	/// Draws the model using the specified renderer and transform.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the model.</param>
	/// <param name="transform"> The transformation to apply, including position, rotation, and scale.</param>
	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.pos, transform.rotation, transform.scale);
	}
	void Model::CalculateRadius()
	{
		_radius = 0;
		for (auto& vert : _verts) {
			float length = vert.Length();
			if (length > _radius) _radius = length;
		}
	}
}