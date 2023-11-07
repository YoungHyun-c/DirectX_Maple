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

	std::string GetLinkedMap()
	{
		return LinkedMap;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::string LinkedMap = "";
	std::shared_ptr<class GameEngineSpriteRenderer> RingPotalSprite;
	std::shared_ptr<GameEngineCollision> RingPotalCol;
};

