#pragma once
#include "GameEngineTexture.h"

// 이미지를 자른다는 개념을 가지거나 할 수 있는 녀석이다.
// 자르는 기능은 만들지 않는다.
class SpriteData
{
public :
	std::shared_ptr<GameEngineTexture> Texture;
	// 이미지를 자르는 용도로 사용한다.
	float4 SpriteData;

	float4 GetScale();
};

class GameEngineSprite : public GameEngineResources<GameEngineSprite>
{
public:
	// constructer destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator = (const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator = (GameEngineSprite&& _Other) noexcept = delete;
	
	// 폴더 위치 알려주면
	// 폴더 위치내부의 텍스처를 전부다 로드해서 스프라이트로 만든다.
	static std::shared_ptr<GameEngineSprite> CreateFolder()
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes();
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes(_Name);
		NewRes->ResCreateCut(_Name, _X, _Y);
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateSingle(std::string_view _Name)
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes(_Name);
		NewRes->ResCreateCut(_Name, 1, 1);
		return NewRes;
	}

	const SpriteData& GetSpriteData(unsigned int _Index);

protected:
	void ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y);

private:
	std::vector<SpriteData> SpriteDatas;
};

