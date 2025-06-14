#pragma once
#include "Singleton.h"
#include "CubeColorComponent.h"
#include "Piramid.h"
#include <string>
#include <unordered_map>
namespace qbert
{
	struct LevelRoundHash {
		std::size_t operator()(const std::pair<int, int>& p) const {
			return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1); //combination of both hashes
		}
	};

	class LevelManager : public dae::Singleton<LevelManager>
	{
	public:
		void StartNextRound();

		CubeLevelParameters GetCurrentCubeLevelParameters();
		
		void SetPiramid(std::weak_ptr<Piramid> pPiramid) { m_pPiramid = std::move(pPiramid); }
		Piramid* const GetPiramid() { return m_pPiramid.lock().get(); }
	private:
		friend class dae::Singleton<LevelManager>;

		CubeLevelParameters GetCubeLevelParameterDefinition(const int level, const int round);
		void WriteAllLevelsToFile();
		void WriteLevelToFile(const CubeLevelParameters& data, const std::string& file_name);
		void ReadAllLevelsFromFile();
		CubeLevelParameters ReadLevelFromFile(const std::string& file_name);

		LevelManager();
		virtual ~LevelManager() = default;

		int m_level{ 1 };
		int m_round{ 1 };
		std::weak_ptr<Piramid> m_pPiramid{};
		std::unordered_map<std::pair<int, int>, CubeLevelParameters, LevelRoundHash> m_levelCubeParameters;
	};
}
