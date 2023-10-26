#include "PreCompile.h"
#include "DamageRenderer.h"
#include "Monster.h"
#include "CravingMonster.h"
#include "MonsterFunction.h"
#include "Player.h"
#include "PlayerValue.h"
#include "GlobalValue.h"

#define MaxDamage 700000000000

DamageRenderer::DamageRenderer()
{

}

DamageRenderer::~DamageRenderer()
{
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End;)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		//float Alpha = (*Vec)[0]->ColorOptionValue.MulColor.a;

		for (int i = 0; i < Vec->size(); i++)
		{
			(*Vec)[i]->Death();
			(*Vec)[i] = nullptr;
		}

		delete (Vec);
		Start = DamageRenderList.erase(Start);
	}
}

void DamageRenderer::Start()
{
	//std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vect = new std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();
	GameEngineSprite::CreateSingle("CriticalNum_0.Png");
	GameEngineSprite::CreateSingle("CriticalNum_1.Png");
	GameEngineSprite::CreateSingle("CriticalNum_2.Png");
	GameEngineSprite::CreateSingle("CriticalNum_3.Png");
	GameEngineSprite::CreateSingle("CriticalNum_4.Png");
	GameEngineSprite::CreateSingle("CriticalNum_5.Png");
	GameEngineSprite::CreateSingle("CriticalNum_6.Png");
	GameEngineSprite::CreateSingle("CriticalNum_7.Png");
	GameEngineSprite::CreateSingle("CriticalNum_8.Png");
	GameEngineSprite::CreateSingle("CriticalNum_9.Png");
}

void DamageRenderer::Update(float _Delta)
{
	// (주스텟*4 + 부스텟) * 총공격력 * 무기상수 * 직업보정 * 스킬퍼뎀 * 크리티컬상수 * 공격력 * 데미지 * 방무보정 * 렙차보정 * 아케인포스보정 * 숙련도 * 스킬최종뎀
	//OneLineDamage = ((Str * 4) + Dex) * AllAttack * WeaponConstant * AdeleCorrection * SkillPercentDam * CriticalConstant * OffensePower * DamagePower *
	//	DefenseCorrection * LevelCorrection * ArcaneCorrection * Proficiency * SkillFinalDamage;

	if (DamageRenderList.size() <= 0)
	{
		Death();
	}

	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End; Start++)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		for (int i = 0; i < (*Start)->size(); i++)
		{
			(*Vec)[i]->Transform.AddLocalPosition({ 0, 50.0f * _Delta});
		}
	}

	CurTime += _Delta;
	if (Disappear <= CurTime)
	{
		DeleteDamage();
		CurTime = 0.0f;
	}
}

void DamageRenderer::PlayerDamageCal()
{
	Str = (PlayerValue::GetValue()->GetPlayerStr());
	Dex = PlayerValue::GetValue()->GetPlayerDex();
	DamagePer = PlayerValue::GetValue()->GetPlayerDamPer();
	BossDamagerPer = PlayerValue::GetValue()->GetPlayerBossDamPer();
	DefenseIgnore = PlayerValue::GetValue()->GetPlayerDefenseIgnore();
	CriticalDam = PlayerValue::GetValue()->GetPlayerCriticalDam();
	AllAttack = PlayerValue::GetValue()->GetPlayerAllAttack();
	AttackPer = PlayerValue::GetValue()->GetPlayerAttackPer();
	ProPertyIgnorePer = PlayerValue::GetValue()->GetPlayerProPertyIgnore();

	OffensePower = ((100 + AttackPer) / 100.0f);
	AllDamagePer = ((100 + DamagePer + BossDamagerPer) / 100.0f);
	DefenseCal = ((100 - (MonsterDefense - MonsterDefense * (DefenseIgnore/100.0f)) * (100 - SkillOption)) / 100.0f);
	MonsterProperty = ((50 + (ProPertyIgnorePer)/2.0f) / 100.0f);

}

void DamageRenderer::PushDamage(GameEngineObject* _Object, size_t _HitCount, size_t _SkillPercentDam, size_t _SkillFinalDamage)
{
	float LastNumYPos = 0.0f;
	for (int j = 0; j < _HitCount; j++)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vect = new std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();
		SkillPercentDam = (_SkillPercentDam / 100.0f);
		SkillFinalDamage = (_SkillFinalDamage / 100.0f);

		PlayerDamageCal();
		
		GameEngineRandom CriticalRan;
		CriticalRan.SetSeed(time(nullptr)+j);
		CriticalRandomDam = CriticalRan.RandomFloat(120, 150);
		Critical = ((CriticalRandomDam + CriticalDam) / 100.0f);
		
		
		OneLineDamage = static_cast<unsigned long long>(((Str * 4) + Dex) * AllAttack * WeaponConstant * AdeleCorrection * SkillPercentDam * Critical * OffensePower * DamagePower *
			DefenseCal * LevelCorrection * ArcaneCorrection * Proficiency * SkillFinalDamage);

		if (_Object->GetName() == "Boss")
		{
			DefenseCal = ((100 - (BossDefense - BossDefense * (DefenseIgnore / 100.0f)) * (100 - SkillOption)) / 100.0f);
			OneLineDamage = static_cast<unsigned long long>(((Str * 4) + Dex) * AllAttack * WeaponConstant * AdeleCorrection * SkillPercentDam * Critical * OffensePower * AllDamagePer *
				DefenseCal * LevelCorrection * MonsterProperty * ArcaneCorrection * Proficiency * SkillFinalDamage);
		}
		if (_Object->GetName() == "Mugong")
		{
			MugongDefense = GlobalValue::GetMonsterValue()->GetMugongDefenseValue();
			DefenseCal = ((100 - (MugongDefense - MugongDefense * (DefenseIgnore / 100.0f)) * (100 - SkillOption)) / 100.0f);
			OneLineDamage = static_cast<unsigned long long>(((Str * 4) + Dex) * AllAttack * WeaponConstant * AdeleCorrection * SkillPercentDam * Critical * OffensePower * DamagePower *
				DefenseCal * LevelCorrection * ArcaneCorrection * Proficiency * SkillFinalDamage);
		}

		if (OneLineDamage >= MaxDamage)
		{
			OneLineDamage = MaxDamage;
		}

		SumDamage += OneLineDamage;
		std::string CurDamage = "OneLineDamage : ";
		CurDamage += std::to_string(static_cast<unsigned long long>(OneLineDamage));
		CurDamage += "\n";
		OutputDebugStringA(CurDamage.c_str());

		// 몬스터에게 데미지
		if (_Object->GetName() == "CravingDiebody")
		{
			_Object->GetParentObject()->GetDynamic_Cast_This<MonsterFunction>()->Hit(OneLineDamage, false);
		}
		else
		{
			_Object->GetParentObject()->GetDynamic_Cast_This<MonsterFunction>()->Hit(OneLineDamage, true);
		}


		int NumArr[15] = { 0, };
		int Digit;

		for (Digit = 0; OneLineDamage > 0; Digit++)
		{
			NumArr[Digit] = OneLineDamage % 10;
			OneLineDamage /= 10;
		}

		Vect->reserve(Digit);

		//float LastNumYPos;
		/*if (DamageRenderList.size() > 0)
		{
			LastNumYPos = (*DamageRenderList.back())[0]->Transform.GetLocalPosition().Y;
		}
		else
		{
			LastNumYPos = 0.0f;
		}*/


		//for (int k = 0; k < _HitCount; j++)
		{
			for (int i = Digit; i > 0; i--)
			{
				std::string TextureName = "CriticalNum_" + std::to_string(NumArr[i - 1]) + ".png";

				NewNumberRender = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::DamageRender);
				NewNumberRender->SetSprite(TextureName);
				NewNumberRender->Transform.SetWorldPosition({ (_Object->Transform.GetWorldPosition().X + 150.0f - (i - 1) * 32.0f), _Object->Transform.GetWorldPosition().Y + LastNumYPos + 150.0f });
				Vect->push_back(NewNumberRender);
			}
			LastNumYPos += 32.0f;
		}
		DamageRenderList.push_back(Vect);
	}
	int a = 0;
}


void DamageRenderer::DeleteDamage()
{
	if (DamageRenderList.size() <= 0)
	{
		return;
	}

	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End;)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		{
			for (int i = 0; i < (*Start)->size(); i++)
			{
				(*Vec)[i]->Death();
				(*Vec)[i] = nullptr;
			}

			delete (Vec);
			Start = DamageRenderList.erase(Start);

			continue;
		}

		Start++;
	}
}