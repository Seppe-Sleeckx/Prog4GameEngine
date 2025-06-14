#pragma once
#include "Component.h"
#include "SDL_rect.h"
#include <queue>
namespace qbert {
	enum class CubeColor
	{
		Aquamarine_Red,
		Aquamarine_Yellow,
		Aquamarine_Blue,
		Brown_Blue,
		Brown_Sand,
		Brown_Green,
	};

	struct CubeLevelParameters
	{
		CubeLevelParameters() = default;
		CubeLevelParameters(const CubeColor start_color, const std::queue<CubeColor> future_colors, const CubeColor desired_color, bool looping = false) : StartColor{ start_color }, FutureColors{ future_colors }, DesiredColor{ desired_color }, Looping{ looping } {}

		CubeColor StartColor = CubeColor::Aquamarine_Red;
		std::queue<CubeColor> FutureColors{};
		CubeColor DesiredColor = CubeColor::Aquamarine_Blue;
		bool Looping = false;
	};
}

namespace qbert
{
	class CubeColorComponent final : public dae::Component
	{
	public:
		CubeColorComponent(std::shared_ptr<dae::GameObject> pOwner, const CubeLevelParameters& params);
		virtual ~CubeColorComponent() = default;

		bool IsAtDesiredColor() const { return m_currentColor == m_desiredColor; }
		void SetNextColor();
	private:
		void SetNewCubeColor(const qbert::CubeColor new_color);

		qbert::CubeColor m_currentColor;
		std::queue<qbert::CubeColor> m_futureColors;
		qbert::CubeColor m_desiredColor;
		bool m_looping;
	};
}