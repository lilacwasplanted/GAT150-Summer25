#include "Time.h"

namespace viper {
	void Time::Tick()
	{
		clock::time_point now = clock::now();
		m_time = std::chrono::duration<float>(now - m_startTime).count();
		m_deltaTime = std::chrono::duration<float>(now - m_frameTime).count();
		m_frameTime = now;
	}
}
