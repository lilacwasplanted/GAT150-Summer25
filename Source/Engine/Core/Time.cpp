#include "Time.h"

namespace viper {
	void Time::Tick()
	{
		clock::time_point now = clock::now();
		m_time = chrono::duration<float>(now - m_startTime).count();
		m_deltaTime = chrono::duration<float>(now - m_frameTime).count();
		m_frameTime = now;
	}
}
