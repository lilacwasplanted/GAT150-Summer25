#include "Time.h"

namespace viper{
	void viper::Time::Tick()
	{
		clock::time_point now = clock::now();
		_time = std::chrono::duration<float>(now - _startTime).count();
		_deltaTime = std::chrono::duration<float>(now - _frameTime).count();
		_frameTime = now;

	}
}
