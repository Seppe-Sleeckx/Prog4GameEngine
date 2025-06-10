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

namespace dae
{
	class CubeColorComponent final : public Component
	{
	public:

	private:
		void SetNewCubeColor(const qbert::CubeColor new_color);

		qbert::CubeColor m_cubeColor{ qbert::CubeColor::Aquamarine_Red };
	};
}