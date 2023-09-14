#include "PreCompile.h"
#include "GameEngineTileMap.h"
#include "GameEngineTransform.h"
#include "GameEngineConstantBuffer.h"

GameEngineTileMap::GameEngineTileMap()
{

}

GameEngineTileMap::~GameEngineTileMap()
{

}

void GameEngineTileMap::CreateTileMap(const CreateTileParameter& _Parameter)
{
	Tiles.resize(_Parameter.TileCountY);
	
	for (size_t i = 0; i < _Parameter.TileCountY; i++)
	{
		Tiles[i].resize(_Parameter.TileCountX);
	}

	DefaultSprite = GameEngineSprite::Find(_Parameter.SpriteName);

	TileData = _Parameter;
	TileData.TileScale.Z = 1.0f;
}

void GameEngineTileMap::SetTile(const SetTileParameter& _Parameter)
{
	if (Tiles.size() <= _Parameter.Y)
	{
		MsgBoxAssert("타일 인데스를 Y 오버했습니다.");
	}

	if (Tiles[_Parameter.Y].size() <= _Parameter.X)
	{
		MsgBoxAssert("타일 인덱스를 X 오버했습니다.");
	}

	Tile& CurTile = Tiles[_Parameter.Y][_Parameter.X];

	if (_Parameter.SpriteName.empty())
	{
		CurTile.Data = DefaultSprite->GetSpriteData(_Parameter.Index);
	}
	else
	{
		std::shared_ptr<GameEngineSprite> FindSprite = GameEngineSprite::Find(_Parameter.SpriteName);
		CurTile.Data = FindSprite->GetSpriteData(_Parameter.Index);
	}

	CurTile.Index = _Parameter.Index;
}

void GameEngineTileMap::Render(GameEngineCamera* _Camera, float _Delta)
{
	ResSetting();

	TransformData Data;
	for (size_t y = 0; y < Tiles.size(); y++)
	{
		for (size_t x = 0; x < Tiles[y].size(); x++)
		{
			// 이게 100 x 100번 만큼
			//if (카메라에 나오지 않는다면)
			//{
			//	continue;
			//}


			std::shared_ptr<GameEngineConstantBuffer> TransBuffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex);

			if (nullptr != TransBuffer)
			{
				float4 Pos;
				Pos = Transform.GetWorldPosition();
				Pos.X += TileData.TileScale.X * x + TileData.TileScale.hX();
				Pos.Y -= TileData.TileScale.Y * y + TileData.TileScale.hX();

				Data = Transform.GetConstTransformDataRef();
				Data.Position = Pos;
				Data.Scale = TileData.TileScale;
				Data.LocalCalculation(); // 로컬 월드 생성

				Data.ParentMatrix = Transform.GetConstTransformDataRef().WorldMatrix;
				Data.WorldMatrix = Data.LocalWorldMatrix * Data.ParentMatrix;
				Data.WorldViewProjectionCalculation();
				// 내 행렬을 전부다 계산하고 넘긴다.

				TransBuffer->ChangeData(Data);
				TransBuffer->Setting(0);
			}

			SpriteData& TileSprite = Tiles[y][x].Data;

			std::shared_ptr<GameEngineConstantBuffer> SpriteBuffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex);
			if (nullptr != SpriteBuffer)
			{
				SpriteBuffer->ChangeData(TileSprite.SpritePivot);
				SpriteBuffer->Setting(1);
			}

			Tiles[y][x].Data.Texture->PSSetting(0);

			Draw();
		}
	}
}