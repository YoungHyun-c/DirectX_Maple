#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineState.h>

enum SkillsName
{
	GreenSkill,
	PurPleSkill,
	BallSkill,
	Max,
};

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

	void SkillUseKey(SkillsName _Name);
	bool SkillUseCheck();

	void Update(float _Delta) override;

protected:
	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void Start() override;

	void CreateGreenSkill();
	void CreatePurpleSkill();
	void CreateBallSkill();
private:
	class Skills
	{
	public:
		bool SkillControl;
		float MaxCoolTime;
		float CurCoolTime;
		float4 SkillUsePos;
		ActorDir SkillUseDir = ActorDir::Max;
		int TargetCollisionOrder;
		GameEngineState SkillState;

		void Update(float _Delta)
		{
			SkillState.Update(_Delta);
		}
	};

	Skills* CurSkill = nullptr;
	SkillsName SkillNameValue = SkillsName::Max;
	std::map<const SkillsName, Skills> BossSkill;
};

