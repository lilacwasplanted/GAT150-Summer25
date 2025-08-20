#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

namespace viper::math {
	constexpr float pi = 3.1415926535897932384626433832795f;
	constexpr float twoPi = 2 * pi;
	constexpr float halfPi = pi * 0.5f;

	/// <summary>
	/// Converts an angle from radians to degrees.
	/// </summary>
	/// <param name="rad">The angle in radians to convert.</param>
	/// <returns>The equivalent angle in degrees.</returns>
	constexpr float radToDeg(float rad) { return rad * (180 / pi); }

	/// <summary>
	/// Converts an angle from degrees to radians.
	/// </summary>
	/// <param name="deg">The angle in degrees to convert.</param>
	/// <returns>The angle in radians.</returns>
	constexpr float degToRad(float deg) { return deg * (pi / 180); }

	/// <summary>
	/// Wraps an integer value into the range [min, max), cycling around if the value is outside the range.
	/// </summary>
	/// <param name="value">The integer value to wrap.</param>
	/// <param name="min">The inclusive lower bound of the range.</param>
	/// <param name="max">The exclusive upper bound of the range.</param>
	/// <returns>The wrapped integer value within the range [min, max).</returns>
	constexpr int wrap(int value, int min, int max) {
		int range = max - min;				// calculate range of wrap
		int result = (value - min) % range; // shift value so range starts at 0
		if (result < 0) result += range;	// wrap forward if result is negative (value < min)
						
		return min + result; // shift the result back to [min, max) range
	}
		
	/// <summary>
	/// Wraps a floating-point value into the range [min, max).
	/// </summary>
	/// <param name="value">The value to be wrapped.</param>
	/// <param name="min">The inclusive lower bound of the range.</param>
	/// <param name="max">The exclusive upper bound of the range.</param>
	/// <returns>The wrapped value within the range [min, max).</returns>
	inline float wrap(float value, float min, float max) {
		float range = max - min;						// calculate range of wrap
		float result = std::fmodf(value - min, range);	// shift value so range starts at 0
		if (result < 0) result += range;				// wrap forward if result is negative (value < min)

		return min + result; // shift the result back to [min, max) range
	}

	/// <summary>
	/// Determines the sign of a number.
	/// </summary>
	/// <typeparam name="T">The type of the value to check. Must support comparison with zero and conversion from integer literals.</typeparam>
	/// <param name="v">The value whose sign is to be determined.</param>
	/// <returns>Returns -1 if the value is negative, 1 if positive, and 0 if zero.</returns>
	template<typename T>
	inline T sign(T v) {
		return (v < 0) ? (T)-1 : (v > 0) ? (T)1 : (T)0;
	}

	using std::min;
	using std::max;
	using std::clamp;
	using std::sqrt;
	using std::sqrtf;
	using std::acos;
	using std::acosf;
	using std::sin;
	using std::sinf;
	using std::cos;
	using std::cosf;
	using std::atan2;
	using std::atan2f;
}
