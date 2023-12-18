#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineState.h>

// Ό³Έν :
class BossSkillManager : public GameEngineActor
{
public:
	static BossSkillManager* BossSkillEffectManager;
public:
	// constructer destructer
	BossSkillManager();
	~BossSkillManager();

	// delete Function
	BossSkillManager(const BossSkillManager& _Other) = delete;
	BossSkillManager(BossSkillManager&& _Other) noexcept = delete;
	BossSkillManager& operator = (const BossSkillManager& _Other) = delete;
	BossSkillManager& operator = (BossSkillManager&& _Other) noexcept = delete;

	void SkillUseKey(const char& _Value);
	bool SkillUseCheck();

	void Update(float _Delta) override;

protected:
	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void Start() override;

private:

	class Skill
	{
	public:
		bool IsControll;
		float MaxCoolTime;
		float CurCoolTime;
		float4 SkillUsePos;
		ActorDir SkillUseDir = ActorDir::Max;
		int TargetCollisionOrder;
		GameEngineState StateTest;

		void Update(float _Delta)
		{
			StateTest.Update(_Delta);
		}
	};

	Skill* CurSkill = nullptr;
	std::map<const char, Skill> SkillState;

	int Green = 0;
	int Purple = 2;

	bool GreenAttack = false;
	bool PurpleAttack = false;
	
	bool BallAttack = false;
};

