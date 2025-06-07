#pragma once
#include "glm.hpp"
#include <memory>

struct IsometricGrid
{
	explicit IsometricGrid(float tile_width, float tile_height) :tile_height{ tile_height }, tile_width{ tile_width } {};

	glm::vec2 WorldToIsometricGridSpace(const glm::vec2& world_coord)
	{
		float x = world_coord.x - origin.x;
		float y = world_coord.y - origin.y;

		float isoX = ((y / tile_height) + (x / tile_width)) / 2;
		float isoY = ((y / tile_height) - (x / tile_width)) / 2;

		return glm::vec2(isoX, isoY);
	}

	glm::vec2 IsometricGridToWorldSpace(const glm::vec2& iso_coord)
	{
		float srcX = ((iso_coord.x - iso_coord.y) + (tile_width / 2.f)) + origin.x;
		float srcY = ((iso_coord.x + iso_coord.y) + (tile_height / 2.f)) + origin.y;

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

	glm::vec2 ToWorldSpace()
	{
		return pGrid->IsometricGridToWorldSpace(position);
	}

	std::shared_ptr<IsometricGrid> pGrid;
	glm::vec2 position;
};