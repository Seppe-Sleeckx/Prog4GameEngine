#pragma once
#include "Component.h"
#include <map>
#include "SDL_rect.h"
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
}

namespace qbert
{
	class CubeColorComponent final : public dae::Component
	{
	public:
		void SetNewCubeColor(const qbert::CubeColor new_color);
	private:

		qbert::CubeColor m_cubeColor{ qbert::CubeColor::Aquamarine_Red };
	};
}