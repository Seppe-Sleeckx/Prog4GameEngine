#pragma once
#include "Singleton.h"
#include "CubeColorComponent.h"
#include "Piramid.h"
namespace qbert
{
	class LevelManager : public dae::Singleton<LevelManager>
	{
	public:
		const CubeLevelParameters GetCurrentCubeLevelParameters();

		//NextLevel(), NextRound()???

		void StartNextRound();

		void SetPiramid(std::weak_ptr<Piramid> pPiramid) { m_pPiramid = std::move(pPiramid); }
		Piramid* const GetPiramid() { return m_pPiramid.lock().get(); }
	private:
		friend class dae::Singleton<LevelManager>;

		LevelManager() = default;
		virtual ~LevelManager() = default;

		int m_level{ 1 };
		int m_round{ 1 };
		std::weak_ptr<Piramid> m_pPiramid{};
	};
}
