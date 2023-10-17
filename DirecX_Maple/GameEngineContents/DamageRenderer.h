#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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
	float WeaponConstant = 1.34;
	float AdeleCorrection = 0.01;
	//float SkillPercentDam = 4.8f;
	float SkillPercentDam;
	//float CriticalConstant = 2.05f;
	float Critical;
	float CriticalRandomDam;
	float CriticalDam = 70;
	float OffensePower = 2.12f;
	float DamagePower = 1.74f;
	float DefenseCorrection = 0.98f;
	float LevelCorrection = 1.5f;
	float ArcaneCorrection = 1.5f;
	float Proficiency =  0.95f;
	float SkillFinalDamage = 1.0f;
	//float SkillFinalDamage = 2.2f;

	long long OneLineDamage;
	int SumDamage;
	int FinalSumDamage;
	float Disappear = 1.5f;
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

