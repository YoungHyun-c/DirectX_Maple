#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class RingPotalManager : public GameEngineActor
{
public:
	// constructer destructer
	RingPotalManager();
	~RingPotalManager();

	// delete Function
	RingPotalManager(const RingPotalManager& _Other) = delete;
	RingPotalManager(RingPotalManager&& _Other) noexcept = delete;
	RingPotalManager& operator = (const RingPotalManager& _Other) = delete;
	RingPotalManager& operator = (RingPotalManager&& _Other) noexcept = delete;

	void SetLinkedMap(std::string_view _MapName)
	{
		LinkedMap = _MapName;
	}

	void SetLinkedPos(float4 _Pos)
	{
		LinkedPos = _Pos;
	}

	std::string GetLinkedMap()
	{
		return LinkedMap;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::string LinkedMap = "";
	std::shared_ptr<class GameEngineSpriteRenderer> RingPotalSprite;
	std::shared_ptr<GameEngineCollision> RingPotalCol;


	void SetPlayerLinkedPos();

	float4 LinkedPos = { 0, 0 };

	std::shared_ptr<class GameEngineUIRenderer> DarkRenderer;
	bool ChangeLevel = false;
};

