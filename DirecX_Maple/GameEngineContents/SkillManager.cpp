#include "PreCompile.h"
#include <GameEngineBase\GameEngineRandom.h>

#include "SkillManager.h"
//#include "AdeleSkill.h"
#include "SkillFunction.h"
#include "SkillDivide.h"
#include "SkillRuin.h"

#include "DamageRenderer.h"

SkillManager* SkillManager::PlayerSkillManager = nullptr;

#define Hit_Ani_Time 0.05f
#define Hit_Delay 0.1f
#define RandomRange 25

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}


void SkillManager::LevelStart(class GameEngineLevel* _PrevLevel)
{
	PlayerSkillManager = this;
}

void SkillManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void SkillManager::Start()
{
	CreateSkill<SkillDivide>("Divide1");
	CreateSkill<SkillRuin>("Ruin");
}

void SkillManager::Update(float _Delta)
{
	HitPrintUpdate(_Delta);
}

void SkillManager::Release()
{
	std::map<std::string, std::shared_ptr<SkillFunction>>::iterator StartIter = AllSkills.begin();
	std::map<std::string, std::shared_ptr<SkillFunction>>::iterator EndIter = AllSkills.end();

	for (std::pair<const std::string, std::shared_ptr<SkillFunction>>& _Pair : AllSkills)
	{
		if (nullptr != _Pair.second)
		{
			_Pair.second->Release();
			_Pair.second = nullptr;
		}
	}
}

void SkillManager::InitSkill(std::shared_ptr<SkillFunction> _Skill)
{
	_Skill->Init();
	_Skill->Off();
}

void SkillManager::UseSkill(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬 입니다.");
		return;
	}

	std::shared_ptr<SkillFunction> Skill = AllSkills[UpperName.data()];
	Skill->On();
	Skill->UseSkill();
}

bool SkillManager::IsSkillUsing(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬을 사용중으로 보입니다.");
		return false;
	}
	std::shared_ptr<SkillFunction> Skill = AllSkills[UpperName.data()];
	return Skill->IsSkillUsing();
}

void SkillManager::EndSkill(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬로 끝내려 했습니다");
		return;
	}
	std::shared_ptr<SkillFunction> Skill = AllSkills[UpperName.data()];
	Skill->EndSkill();
}

void SkillManager::HitPrint(GameEngineObject* _Object, std::string_view _HitSpriteName, size_t _HitCount 
	,bool _RandomPos /*= true*/, PivotType _PivotType /*= PivotType::Bottom*/)
{
	GameEngineRandom RandomActor;
	std::shared_ptr<HitRenderData> HitData = std::make_shared<HitRenderData>();
	HitData->Object = _Object;
	HitData->HitAnimations.resize(_HitCount);
	HitData->RandomPos.resize(_HitCount);

	/*std::shared_ptr<DamageRenderer> NewDR = GetLevel()->CreateActor<DamageRenderer>();
	NewDR->PushDamage(_Object, _HitCount, 480, 220);*/

	for (size_t i = 0; i < _HitCount; i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> HitAnimation = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::DamageRender);

		if (true == _RandomPos)
		{
			RandomActor.SetSeed(reinterpret_cast<long long>(_Object) + time(nullptr) + i);
			HitData->RandomPos[i].X = RandomActor.RandomFloat(-RandomRange, RandomRange);
			RandomActor.SetSeed(reinterpret_cast<long long>(_Object) + time(nullptr) + i);
			HitData->RandomPos[i].Y = RandomActor.RandomFloat(-RandomRange, RandomRange);
		}

		HitAnimation->CreateAnimation("Hit", _HitSpriteName, Hit_Ani_Time);
		HitAnimation->ChangeAnimation("Hit");
		HitAnimation->Transform.SetWorldPosition(_Object->Transform.GetWorldPosition() + HitData->RandomPos[i]);
		HitAnimation->AutoSpriteSizeOn();
		HitAnimation->SetEndEvent("Hit", [&](GameEngineSpriteRenderer* _Renderer)
			{
				_Renderer->Off();
				_Renderer->Death();
			}
		);
		HitAnimation->Off();
		HitAnimation->SetPivotType(_PivotType);

		HitData->HitAnimations[i] = HitAnimation;
	}

	AllHitRenders.push_back(HitData);
}


void SkillManager::HitPrintUpdate(float _Delta)
{
	std::list<std::shared_ptr<HitRenderData>>::iterator StartIter = AllHitRenders.begin();
	std::list<std::shared_ptr<HitRenderData>>::iterator EndIter = AllHitRenders.end();

	for (; StartIter != EndIter;)
	{
		std::shared_ptr<HitRenderData> CurData = (*StartIter);
		if (CurData->HitAnimations.size() == CurData->CurIndex)
		{
			if (true == CurData->HitAnimations[CurData->CurIndex - 1]->IsCurAnimationEnd())
			{
				CurData->Object = nullptr;
				StartIter = AllHitRenders.erase(StartIter);
				continue;
			}
			++StartIter;
			continue;
		}

		CurData->DelayTime -= _Delta;
		if (0.0f >= CurData->DelayTime)
		{
			CurData->HitAnimations[CurData->CurIndex]->On();
			CurData->CurIndex += 1;
			CurData->DelayTime = Hit_Delay;
		}
		++StartIter;
	}
}