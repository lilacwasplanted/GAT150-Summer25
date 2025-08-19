#pragma once

#include <cmath>
#include <algorithm>
#include <SDL3/SDL.h>

namespace viper::math{
	constexpr float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089f;
	constexpr float twopi = 2 * pi;
	constexpr float halfpi = pi / 2;

	/// <summary>
	/// Converts an angle from radians to degrees.
	/// </summary>
	/// <param name="rad"> The angle in radians to convert.</param>
	/// <returns> The equivalent angle in degrees.</returns>
	constexpr float radToDeg(float rad) { return rad * (180 / pi); }
		
	/// <summary>
	/// Converts an angle from degrees to radians
	/// </summary>
	/// <param name="deg"> The angel in degree to convert</param>
	/// <returns>The angle in radians.</returns>
	constexpr float degToRad(float deg) { return deg * (pi / 180); }

	/// <summary>
	/// Wraps an interger value into the range [min, max) , cycling around if the value i
	/// </summary>
	/// <param name="value">The interger value to wraps</param>
	/// <param name="min">The inclusinve lower bound of the range</param>
	/// <param name="max"> The exclusive upper bound of the range</param>
	/// <returns>The wrapped interger vale within the range [min, max).</returns>
	constexpr int wrap(int value, int min, int max) {
		int range = max - min;							//calculate range of wrap
		int result = (value - min) % range;		    //shift value so range starts at 0
		if (result < 0)  result += range;				//wrap foward if result is negative (value)

		return min + result;			//Shift the result to the [min, max) range
	}


	/// <summary>
	/// Wraps a floating-point value into the range [max,min). 
	/// </summary>
	/// <param name="value">The value into the range [min, max)</param>
	/// <param name="min">The inculsive lower bound of the range</param>
	/// <param name="max">The exculsive upper bound of the range.</param>
	/// <returns>The wrapped value within the range [min, max)</returns>
	inline float wrap(float value, float min, float max) {
		float range = max - min;										//calculate rang of wrap
		float result = fmodf(value - min, range);				//shift value so range starts
		if (result < 0) result += range;								//wrap foward if results is ne
		return min + result;				//Shift the result back to [min, max) range
	}
	/// <summary>
	/// Determines the sign of a given value.
	/// </summary>
	/// <typeparam name="T">The type of the value to check.</typeparam>
	/// <param name="v">The value whose sign is to be determined.</param>
	/// <returns>Returns -1 if the value is negative, 1 if positive, and 0 if zero.</returns>
	template <typename T>
	inline T sign(T v) {
		return (v < 0) ? (T)-1 : (v > 0) ? (T)1 : (T)0;
	}

	using std::min;
	using std::max;
	using std::clamp;
	using std::sqrt;
	using std::sqrtf;
	using std::sin;
	using std::sinf;
	using std::acos;
	using std::acosf;
	using std::cos;
	using std::cosf;
	using std::atan2;
	using std::atan2f;
	
}
