#pragma once
#include "GameEngineTexture.h"

// �̹����� �ڸ��ٴ� ������ �����ų� �� �� �ִ� �༮�̴�.
// �ڸ��� ����� ������ �ʴ´�.
class SpriteData
{
	std::shared_ptr<GameEngineTexture> Texture;
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
	
	// ���� ��ġ �˷��ָ�
	// ���� ��ġ������ �ؽ�ó�� ���δ� �ε��ؼ� ��������Ʈ�� �����.
	static std::shared_ptr<GameEngineSprite> CreateFolder()
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes();
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateCut()
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes();
		return NewRes;
	}

protected:

private:
	std::vector<SpriteData> GameEngineSpriteData;
};

