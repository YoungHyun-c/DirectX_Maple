#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PotalManager : public GameEngineActor
{
public:
	// constructer destructer
	PotalManager();
	~PotalManager();

	// delete Function
	PotalManager(const PotalManager& _Other) = delete;
	PotalManager(PotalManager&& _Other) noexcept = delete;
	PotalManager& operator = (const PotalManager& _Other) = delete;
	PotalManager& operator = (PotalManager&& _Other) noexcept = delete;

	void SetLinkedMap(std::string_view _MapName)
	{
		LinkedMap = _MapName;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::string LinkedMap = "";
	std::shared_ptr<GameEngineCollision> PotalCol;
};

