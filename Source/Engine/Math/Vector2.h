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
		/// <summary>
		/// Calculates the dot product of two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The dot product of the two vectors as a float.</returns>
		float Dot(const Vector2& a, const Vector2& b) const {
			return (a.x * b.x + a.y * b.y);
		}
		/// <summary>
		/// Calculates the angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first vector.</param>
		/// <param name="b">The second vector.</param>
		/// <returns>The angle in radians between the two vectors.</returns>
		float AngleBetween(const Vector2& a, const Vector2& b) const {
			return math::acosf(Dot(a,b));
		}
		/// <summary>
		/// Computes the 2D cross product (determinant) of two vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The scalar value representing the cross product of the two vectors.</returns>
		float Cross(const Vector2& a, const Vector2& b) const {
			return (a.x * b.y - a.y * b.x);
		}
		/// <summary>
		/// Calculates the signed angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first vector.</param>
		/// <param name="b">The second vector.</param>
		/// <returns>The signed angle in radians between vector a and vector b. The sign indicates the direction from a to b.</returns>
		float SignedAngleBetween (const Vector2& a, const Vector2& b) const {
			Vector2 v{ Dot(a, b), Cross(a, b) };
			return v.Angle();
		}
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}
