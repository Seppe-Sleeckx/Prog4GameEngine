#pragma once
#include <chrono>
#include "Singleton.h"

namespace dae {

	class Time final : public dae::Singleton<Time>
	{
	public:
		void SetDeltaTime(const float& delta_time);
		void SetFixedDeltaTime(const float& fixed_delta_time);
		void SetLastTime(const std::chrono::high_resolution_clock::time_point& last_time);

		double GetDeltaTime() const;
		double GetFixedDeltaTime() const;
		std::chrono::high_resolution_clock::time_point GetLastTime() const;
	private:
		friend class Singleton<Time>;
		//Constructor
		Time() = default;

		//Destructor
		~Time() = default;

		//Rule Of 5
		Time(const Time&) = delete;
		Time(Time&&) = delete;
		Time& operator=(const Time&) = delete;
		Time& operator=(Time&&) = delete;

		double m_deltaTime{ 0.0 };
		double m_fixedDeltaTime{ 0.0 };
		std::chrono::high_resolution_clock::time_point m_lastTime{ std::chrono::high_resolution_clock::now() };
	};
}