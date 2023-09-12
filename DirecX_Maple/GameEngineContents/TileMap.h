#pragma once

// Ό³Έν :
class TileMap
{
public:
	// constructer destructer
	TileMap();
	~TileMap();

	// delete Function
	TileMap(const TileMap& _Other) = delete;
	TileMap(TileMap&& _Other) noexcept = delete;
	TileMap& operator = (const TileMap& _Other) = delete;
	TileMap& operator = (TileMap&& _Other) noexcept = delete;

protected:

private:

};

