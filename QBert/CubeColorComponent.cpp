#include "CubeColorComponent.h"
#include "GameObject.h"
#include "Texture2DRenderer.h"
using namespace qbert;

CubeColorComponent::CubeColorComponent(std::shared_ptr<dae::GameObject> pOwner, const CubeLevelParameters& params) : dae::Component(pOwner), m_currentColor{ params.StartColor }, m_futureColors{ params.FutureColors }, m_desiredColor{ params.DesiredColor }, m_looping{ params.Looping } 
{
	SetNewCubeColor(m_currentColor);
}

void CubeColorComponent::SetNextColor()
{
	if (m_looping)
		m_futureColors.push(m_currentColor);
	
	if (std::ssize(m_futureColors) <= 0)
		return;

	auto next_color = m_futureColors.front();
	m_futureColors.pop();
	SetNewCubeColor(next_color);
}

void CubeColorComponent::SetNewCubeColor(const qbert::CubeColor new_cube_color)
{
	m_currentColor = new_cube_color;

	SDL_Rect new_src_rect{};

	switch (m_currentColor)
	{
	case qbert::CubeColor::Aquamarine_Blue:
		new_src_rect = { 0, 224, 32, 32 };
		break;
	case qbert::CubeColor::Aquamarine_Red:
		new_src_rect = { 0, 160, 32, 32 };
		break;
	case qbert::CubeColor::Aquamarine_Yellow:
		new_src_rect = { 0, 192, 32, 32 };
		break;
	case qbert::CubeColor::Brown_Blue:
		new_src_rect = { 80, 160, 32, 32 };
		break;
	case qbert::CubeColor::Brown_Sand:
		new_src_rect = { 80, 192, 32, 32 };
		break;
	case qbert::CubeColor::Brown_Green:
		new_src_rect = { 80, 224, 32, 32 };
		break;
	default:
		new_src_rect = { 0, 0, 0, 0 };
		break;
	}	

	auto texture2d_renderer = GetOwner()->GetComponentByType<dae::Texture2DRenderer>();
	if (texture2d_renderer)
	{
		texture2d_renderer->SetTexture("Qbert.png");
		texture2d_renderer->SetSrcRect(new_src_rect);
	}
}
