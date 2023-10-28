#include "PreCompile.h"
#include "BossSkillManager.h"
#include "BossSkillEffect.h"
#include "JInHillaBoss.h"

BossSkillManager* BossSkillManager::BossSkillEffectManager = nullptr;

BossSkillManager::BossSkillManager()
{

}

BossSkillManager::~BossSkillManager()
{

}

void BossSkillManager::LevelStart(GameEngineLevel* _PrevLevel)
{
	BossSkillEffectManager = this;
}

void BossSkillManager::Start()
{
	{
		SkillState['G'];
		SkillState['P'];
	}

	{
		Skill Skill;
		Skill.IsControll = false;
			
		for (int i = 0; i < 6; i++)
		{
			Skill.StateTest.CreateState(i, {
				.Start =
				[=](class GameEngineState* _Parent)
				{
					if (CurSkill->SkillUseDir == ActorDir::Right)
					{
						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{350.0f + 150 * i, -100.0f, 0.0f});
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i >= 1)
							{
								Green = 1;
							}
							if (i >= 3)
							{
								Green = 2;
							}

							std::string AniName = "GreenTile";
							AniName += std::to_string(Green);
							Effect->ChangeAnimationState(AniName);
						}
						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{-200.0f - 150*i, -100.0f, 0.0f});
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i >= 1)
							{
								Green = 1;
							}
							if (i >= 3)
							{
								Green = 2;
							}
							std::string AniName = "GreenTile";
							AniName += std::to_string(Green);
							Effect->ChangeAnimationState(AniName);
						}
					}


					if (CurSkill->SkillUseDir == ActorDir::Left)
					{
						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -350.0f - 150 * i, -100.0f, 0.0f });
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i >= 1)
							{
								Green = 1;
							}
							if (i >= 3)
							{
								Green = 2;
							}

							std::string AniName = "GreenTile";
							AniName += std::to_string(Green);
							Effect->ChangeAnimationState(AniName);
						}

						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 200.0f + 150 * i, -100.0f, 0.0f });
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i >= 1)
							{
								Green = 1;
							}
							if (i >= 3)
							{
								Green = 2;
							}

							std::string AniName = "GreenTile";
							AniName += std::to_string(Green);
							Effect->ChangeAnimationState(AniName);
						}
					}

				},
				.Stay =
				[=](float DeltaTime, class GameEngineState* _Parent)
				{
					if (0.15f <= _Parent->GetStateTime())
					{
						_Parent->ChangeState(i + 1);
					}
				}
				});
		}

		// 20에서 사용 가능
		Skill.StateTest.CreateState(6, {
			.Start =
			[=](class GameEngineState* _Parent)
			{
					CurSkill = nullptr;
					Green = 0;
					GreenAttack = false;
			} });

		SkillState['G'] = Skill;
	}

	{
		Skill Skill2;
		Skill2.IsControll = false;

		for (int i = 0; i < 6; i++)
		{
			Skill2.StateTest.CreateState(i, {
				.Start =
				[=](class GameEngineState* _Parent)
				{
					if (CurSkill->SkillUseDir == ActorDir::Right)
					{
						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{350.0f + 150 * i, -100.0f, 0.0f});
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i >= 2 && i < 4)
							{
								Purple = 1;
							}
							if (i >= 4)
							{
								Purple = 0;
							}

							std::string AniName = "PurpleTile";
							AniName += std::to_string(Purple);
							Effect->ChangeAnimationState(AniName);
						}
						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{-200.0f - 150 * i, -100.0f, 0.0f});
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i >= 2)
							{
								Purple = 1;
							}
							if (i >= 4)
							{
								Purple = 0;
							}

							std::string AniName = "PurpleTile";
							AniName += std::to_string(Purple);
							Effect->ChangeAnimationState(AniName);
						}
					}


					if (CurSkill->SkillUseDir == ActorDir::Left)
					{
						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -350.0f - 150 * i, -100.0f, 0.0f });
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i >= 2)
							{
								Purple = 1;
							}
							if (i >= 4)
							{
								Purple = 0;
							}

							std::string AniName = "PurpleTile";
							AniName += std::to_string(Purple);
							Effect->ChangeAnimationState(AniName);
						}

						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 200.0f + 150 * i, -100.0f, 0.0f });
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i >= 2)
							{
								Purple = 1;
							}
							if (i >= 4)
							{
								Purple = 0;
							}

							std::string AniName = "PurpleTile";
							AniName += std::to_string(Purple);
							Effect->ChangeAnimationState(AniName);
						}
					}

				},
				.Stay =
				[=](float DeltaTime, class GameEngineState* _Parent)
				{
					if (0.15f <= _Parent->GetStateTime())
					{
						_Parent->ChangeState(i + 1);
					}
				}
				});
		}

		// 20에서 사용 가능
		Skill2.StateTest.CreateState(6, {
			.Start =
			[=](class GameEngineState* _Parent)
			{
					CurSkill = nullptr;
					Purple = 2;
					PurpleAttack = false;
			} });

		SkillState['P'] = Skill2;
	}
}

void BossSkillManager::Update(float _Delta)
{
	if (nullptr != CurSkill)
	{
		CurSkill->Update(_Delta);
	}
}

bool BossSkillManager::SkillUseCheck()
{
	if (nullptr != CurSkill)
	{
		return false;
	}

	for (std::pair<const char, Skill>& pair : SkillState)
	{
		if (GreenAttack == true && pair.first == 'G')
		{
			Skill& UseSkill = pair.second;

			CurSkill = &UseSkill;
			CurSkill->SkillUsePos = JinHillaBoss::GetMainBoss()->Transform.GetWorldPosition();
			CurSkill->SkillUseDir = JinHillaBoss::GetMainBoss()->GetDir();
			UseSkill.StateTest.ChangeState(0);
			return true;
		}

		if (PurpleAttack = true && pair.first == 'P')
		{
			Skill& UseSkill = pair.second;
			CurSkill = &UseSkill;
			CurSkill->SkillUsePos = JinHillaBoss::GetMainBoss()->Transform.GetWorldPosition();
			CurSkill->SkillUseDir = JinHillaBoss::GetMainBoss()->GetDir();
			UseSkill.StateTest.ChangeState(0);
			return true;
		}
	}

	return false;
}

void BossSkillManager::SkillUseKey(const char& _Value)
{
	if (_Value == 'G')
	{
		SkillState['G'];
		GreenAttack = true;
		SkillUseCheck();
	}

	if (_Value == 'P')
	{
		SkillState['P'];
		PurpleAttack = true;
		SkillUseCheck();
	}
}