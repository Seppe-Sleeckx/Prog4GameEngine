#pragma once
#include <memory>
#include "GameObject.h"
#include <SDL_rect.h>
#include "Piramid.h"

namespace qbert
{
	class CoilyState
	{
	public:
		CoilyState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid) : m_pCoilyObject{ std::move(pCoilyObject) }, m_pPiramid{ std::move(pPiramid) } {};
		virtual ~CoilyState() = default;

		//Rule of 5
		CoilyState(const CoilyState& other) = delete;
		CoilyState(CoilyState&& other) = delete;
		CoilyState& operator=(const CoilyState& other) = delete;
		CoilyState& operator=(CoilyState&& other) = delete;

		virtual void OnEnter() = 0;
		virtual std::unique_ptr<CoilyState> Update() = 0;
		virtual std::unique_ptr<CoilyState> FixedUpdate() = 0;

	protected:
		std::weak_ptr<dae::GameObject> m_pCoilyObject;
		std::weak_ptr<qbert::Piramid> m_pPiramid;
	};
}