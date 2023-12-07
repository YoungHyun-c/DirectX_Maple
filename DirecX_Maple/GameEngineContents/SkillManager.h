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

	//GameEngineObject* HitObjectData = nullptr;

	bool IsSet = false;

	bool IsAttack = false;
	
	// 사운드 변경할꺼
	GameEngineSoundPlayer HitPlay;
};

