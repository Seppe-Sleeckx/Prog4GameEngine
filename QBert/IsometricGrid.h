#pragma once
#include "glm.hpp"
#include <memory>

struct IsometricGrid
{
	explicit IsometricGrid(float tile_width, float tile_height) :tile_height{ tile_height }, tile_width{ tile_width } {};

	glm::vec2 LocalToIsometricGridSpace(const glm::vec2& local_coord)
	{
		float x = local_coord.x - origin.x;
		float y = local_coord.y - origin.y;

		float isoX = ((y / tile_height) + (x / tile_width)) / 2;
		float isoY = ((y / tile_height) - (x / tile_width)) / 2;

		return glm::vec2(isoX, isoY);
	}

	glm::vec2 IsometricGridToWorldSpace(const glm::vec2& iso_coord)
	{
		const float& x = iso_coord.x;
		const float& y = iso_coord.y;

		float srcX = (x * tile_width * 0.5f) + (y * tile_height * -0.5f);
		float srcY = (x * tile_height * 0.75f) + (y * tile_height * 0.75f);
		srcY += tile_height / 2.f;

		srcX += origin.x;
		srcY += origin.y;
		return glm::vec2(srcX, srcY);
	}

	glm::vec2 origin{ 0.f,0.f };
	float tile_height;
	float tile_width;
};

struct IsometricGridPosition
{
	IsometricGridPosition(float x, float y, const std::shared_ptr<IsometricGrid>& pGrid) : IsometricGridPosition(glm::vec2(x, y), pGrid) {};
	IsometricGridPosition(const glm::vec2& pos, const std::shared_ptr<IsometricGrid>& pGrid) : position{ pos }, pGrid{ pGrid } {};

	glm::vec2 ToWorldSpace(){ return pGrid->IsometricGridToWorldSpace(position); }

	std::shared_ptr<IsometricGrid> pGrid;
	glm::vec2 position;
};