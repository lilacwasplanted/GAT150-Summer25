#pragma once
#include <chrono>

namespace viper {
	class Time {
	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		Time() {
			_startTime = clock::now();
			_frameTime = clock::now();
		}

		void Tick();
		void Reset() { _startTime = clock::now(); }

		float GetTime() const { return _time; }
		float GetDeltaTime() const { return _deltaTime; }

		void SetTimeScale(float timeScale) { _timeScale = timeScale; }

	private:
		float _time = 0;
		float _deltaTime = 0;
		float _timeScale = 1;

		clock::time_point _startTime;
		clock::time_point _frameTime;
	};
}