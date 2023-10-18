#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class DamageRenderer : public GameEngineActor
{
public:
	// constructer destructer
	DamageRenderer();
	~DamageRenderer();

	// delete Function
	DamageRenderer(const DamageRenderer& _Other) = delete;
	DamageRenderer(DamageRenderer&& _Other) noexcept = delete;
	DamageRenderer& operator = (const DamageRenderer& _Other) = delete;
	DamageRenderer& operator = (DamageRenderer&& _Other) noexcept = delete;

	void PushDamage(GameEngineObject* _Object, size_t _HitCount, size_t _SkillPercentDam, size_t _SkillFinalDamage);
	//void PushDamage(size_t _SkillPercentDam);
	void DeleteDamage();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	int Str = 40182;
	int Dex = 4354;
	int AllAttack = 4772;
	float WeaponConstant = 1.34f;
	float AdeleCorrection = 0.01f;

	//float SkillFinalDamage = 2.2f;
	//float CriticalConstant = 2.05f;

	float SkillPercentDam = 0.0f;
	float SkillFinalDamage = 1.0f;
	float Critical = 0.0f;
	float CriticalRandomDam = 0.0f;
	float CriticalDam = 70.0f;
	float OffensePower = 2.12f;
	float DamagePower = 1.74f;
	float DefenseCorrection = 0.98f;
	float LevelCorrection = 1.5f;
	float ArcaneCorrection = 1.5f;
	float Proficiency =  0.95f;

	long long OneLineDamage = 0;
	long long SumDamage = 0;
	int FinalSumDamage = 0;
	float Disappear = 1.0f;
	float CurTime = 0.0f;
	float LastNumYPos = 0.0f;
	bool IsSet = false;


	std::shared_ptr<GameEngineSpriteRenderer> Render0;
	std::shared_ptr<GameEngineSpriteRenderer> Render1;
	std::shared_ptr<GameEngineSpriteRenderer> Render2;
	std::shared_ptr<GameEngineSpriteRenderer> Render3;
	std::shared_ptr<GameEngineSpriteRenderer> Render4;
	std::shared_ptr<GameEngineSpriteRenderer> Render5;
	std::shared_ptr<GameEngineSpriteRenderer> Render6;
	std::shared_ptr<GameEngineSpriteRenderer> Render7;
	std::shared_ptr<GameEngineSpriteRenderer> Render8;
	std::shared_ptr<GameEngineSpriteRenderer> Render9;

	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*> DamageRenderList;
	std::shared_ptr<GameEngineSpriteRenderer> NewNumberRender;
};

