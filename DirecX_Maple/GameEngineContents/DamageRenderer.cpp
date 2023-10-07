#include "PreCompile.h"
#include "DamageRenderer.h"
#include "Monster.h"

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
		return;
	}

	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End; Start++)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		for (int i = 0; i < (*Start)->size(); i++)
		{
			(*Vec)[i]->Transform.AddLocalPosition({ 0, 20.0f * _Delta});
		}
	}

	CurTime += _Delta;
	if (Disappear <= CurTime)
	{
		DeleteDamage();
		CurTime = 0.0f;
	}

}

void DamageRenderer::PushDamage(int _SkillDamage)
{
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vect = new std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();
	SkillPercentDam = (_SkillDamage / 100.0f );
	OneLineDamage = ((Str * 4) + Dex) * AllAttack * WeaponConstant * AdeleCorrection * SkillPercentDam * CriticalConstant * OffensePower * DamagePower *
		DefenseCorrection * LevelCorrection * ArcaneCorrection * Proficiency * SkillFinalDamage;
	
	std::string CurDamage = "OneLineDamage : ";
	CurDamage += std::to_string(static_cast<int>(OneLineDamage));
	CurDamage += "\n";
	OutputDebugStringA(CurDamage.c_str());

	int NumArr[14] = { 0, };
	int Digit;

	for (Digit = 0; OneLineDamage > 0; Digit++)
	{
		NumArr[Digit] = OneLineDamage % 10;
		OneLineDamage /= 10;
	}

	Vect->reserve(Digit);


	for (int i = 0; i < 7; i++)
	{
		for (int i = Digit; i > 0; i--)
		{
			std::string TextureName = "CriticalNum_" + std::to_string(NumArr[i - 1]) + ".png";

			NewNumberRender = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::DamageRender);
			NewNumberRender->SetSprite(TextureName);
			//NewNumberRender->Transform.SetLocalPosition({ ((Digit / 2) - (i - 1)) * 32.0f + (16.0f * (Digit % 2)), LastNumYPos + 18.0f });
			NewNumberRender->Transform.SetWorldPosition({ (Monster::Monsters->Transform.GetLocalPosition().X + 150.0f - (i - 1) * 32.0f), Monster::Monsters->Transform.GetLocalPosition().Y + LastNumYPos  + 50.0f });
			Vect->push_back(NewNumberRender);
		}
		LastNumYPos += 30.0f;
	}

	DamageRenderList.push_back(Vect);

	//float Pos = (*DamageRenderList.back())[0]->Transform.GetLocalPosition().Y;
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
			}

			delete (Vec);
			Start = DamageRenderList.erase(Start);

			continue;
		}

		Start++;
	}
}