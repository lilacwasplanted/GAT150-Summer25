#pragma once
#include"Math.h"
#include <cassert>

namespace viper {

	template<typename T>
	struct Vector2 {

		union{
			struct { T x, y; };
			struct { T u, v; };
		 };
		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y };  }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y* v.y };  }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2& operator += (const Vector2& v) { x += v.x;	y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x;		y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x;	y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x;	y /= v.y; return *this; }


		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (float s)  {x += s;	y += s; return *this; }
		Vector2& operator -= (float s)  {x -= s;	y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s;	y *= s; return *this;}
		Vector2& operator /= (float s) { x /= s;	y /= s; return *this; }

		//sqrt (x*x + y*y)
		
		/// <summary>
		/// Calculates the squared length (magnatitude) of a 2D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x and y components of the vector.</returns>
		float LengthSqr() const { return((x * x) + (y * y)); }
		/// <summary>
		/// Calculates the length(magnatitude) of the vector
		/// </summary>
		/// <returns>The length of the vector as a floating-point value.</returns>
		float Length() const { return viper::math::sqrtf(LengthSqr()); }
		/// <summary>
		/// Returns a normalized (unit length) version of the vector.
		/// </summary>
		/// <returns>A Vector2 representing the normalized form of the current vector</returns>
		Vector2 Normalized() const { return *this / Length(); }
		/// <summary>
		/// Returns the angle, in radians, between the positive x-axis and the point (x, y).
		/// </summary>
		/// <returns> Then angle in radians, computed using atan2f(y,x).</returns>
		float Angle() const { return math::atan2f(y, x); };
		/// <summary>
		/// Returns a new vector that is the result of rotating this vector by the specified 
		/// </summary>
		/// <param name="radians">The angle to rotate this vector by the vector, in radians.</param>
		/// <returns>A new Vector2 representing the rotated vector.</returns>
		Vector2 Rotate(float radians) const {
			Vector2 v;
			
			v.x = x * math::cosf(radians) - y * math::sinf(radians);
			v.y =  x * math::sinf(radians) + y * math::cosf(radians);

			return v;
		}
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}
