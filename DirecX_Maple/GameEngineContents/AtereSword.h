#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum struct AtereSwordActor
{
	Appear,
	Loop,
	End,
	Max,
};

// Ό³Έν :
class AtereSword : public GameEngineActor
{
public:
	// constructer destructer
	AtereSword();
	~AtereSword();

	// delete Function
	AtereSword(const AtereSword& _Other) = delete;
	AtereSword(AtereSword&& _Other) noexcept = delete;
	AtereSword& operator = (const AtereSword& _Other) = delete;
	AtereSword& operator = (AtereSword&& _Other) noexcept = delete;

	void ChangeState(AtereSwordActor _State);
	void StateUpdate(float _Delta);

protected:
	void Start() override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void Update(float _Delta);

	void AppearStart();
	void LoopStart();
	void EndStart();
	
	void AppearUpdate(float _Delta);
	void LoopUpdate(float _Delta);
	void EndUpdate(float _Delta);
	

private:

	std::shared_ptr<GameEngineUIRenderer> SwordAnimation;
	AtereSwordActor SwordState = AtereSwordActor::Max;
};

