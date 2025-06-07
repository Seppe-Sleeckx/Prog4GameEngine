#include "GameTime.h"
using namespace dae;

void Time::SetDeltaTime(const float& delta_time)
{
	m_deltaTime = delta_time;
}

void Time::SetFixedDeltaTime(const float& fixed_delta_time)
{
	m_fixedDeltaTime = fixed_delta_time;
}

void Time::SetLastTime(const std::chrono::high_resolution_clock::time_point& last_time)
{
	m_lastTime = last_time;
}

double Time::GetDeltaTime() const
{
	return m_deltaTime;
}

double Time::GetFixedDeltaTime() const
{
	return m_fixedDeltaTime;
}

std::chrono::high_resolution_clock::time_point Time::GetLastTime() const
{
	return m_lastTime;
}