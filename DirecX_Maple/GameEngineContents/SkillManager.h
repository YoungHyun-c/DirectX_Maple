#pragma once

struct HitRenderData
{
	friend class SkillManager;
private:
	bool AniEnd = false;
	int CurIndex = 0;
	float DelayTime = 0.0f;

	GameEngineObject* Object = nullptr;

	std::vector<float4> RandomPos;
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> HitAnimations;

};

class SkillManager : public GameEngineActor
{
public:
	static SkillManager* PlayerSkillManager;
public:
	// constructer destructer
	SkillManager();
	~SkillManager();

	// delete function
	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;

	void UseSkill(std::string_view _SkillName);
	void EndSkill(std::string_view _SkillName);
	bool IsSkillUsing(std::string_view _SkillName);

	template<typename SkillName>
	void CreateSkill( std::string_view _SkillName)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
		std::shared_ptr<class SkillFunction> NewSkill = GetLevel()->CreateActor<SkillName>();
		if (false == AllSkills.contains(UpperName))
		{
			AllSkills[UpperName] = std::shared_ptr<class SkillFunction>();
		}
		AllSkills[UpperName] = NewSkill;
		InitSkill(NewSkill);
	}

	void HitPrint(GameEngineObject* _Object, std::string_view _HitSpriteName, size_t _HitCount, bool _RandomPos = true, PivotType _PivotType = PivotType::Bottom);

protected:
	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	void InitSkill(std::shared_ptr<class SkillFunction> _Skill);
	void HitPrintUpdate(float _Delta);

	std::map<std::string, std::shared_ptr<class SkillFunction>> AllSkills;
	std::list<std::shared_ptr<HitRenderData>> AllHitRenders;



	// µ¥¹ÌÁö ·»´õ
	int Str = 40182;
	int Dex = 4354;
	int AllAttack = 4772;
	float WeaponConstant = 1.34;
	float AdeleCorrection = 0.01;
	//float SkillPercentDam = 4.8f;
	GameEngineObject* HitObjectData;
	size_t HitCount;
	size_t SkillPercentDam;
	size_t SkillFinalDamage;
	//float CriticalConstant = 2.05f;
	float Critical;
	float CriticalRandomDam;
	float CriticalDam = 70;
	float OffensePower = 2.12f;
	float DamagePower = 1.74f;
	float DefenseCorrection = 0.98f;
	float LevelCorrection = 1.5f;
	float ArcaneCorrection = 1.5f;
	float Proficiency = 0.95f;

	int OneLineDamage;
	float Disappear = 1.5f;
	float CurTime = 0.0f;
	float LastNumYPos = 0.0f;
	bool IsSet = false;

	bool IsAttack = false;
};

