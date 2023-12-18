#include "PreCompile.h"
#include "BossSkillManager.h"
#include "BossSkillEffect.h"
#include "BossSkillBall.h"
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
		SkillState['B'];
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
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{400.0f + 150 * i, -100.0f, 0.0f});
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
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i == 0)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 20.0f, -100.0f, 0.0f });
							}
							if (i >= 1)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -230.0f - 200.0f * (i-1), -100.0f, 0.0f});
								Green = 1;
							}
							if (i >= 3)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -200.0f - 150 * i, -100.0f, 0.0f });
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
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -400.0f - 150 * i, -100.0f, 0.0f });
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
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i == 0)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -20.0f, -100.0f, 0.0f });
							}
							if (i >= 1)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 230.0f + 200.0f * (i - 1), -100.0f, 0.0f });
								Green = 1;
							}
							if (i >= 3)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 200.0f + 150 * i, -100.0f, 0.0f });
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
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i == 0)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 100.0f, -100.0f, 0.0f });
							}
							if (i == 1)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 250.0f, -100.0f, 0.0f });
							}
							if (i >= 2 && i < 4)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 125.0f + 150.0f * i, -100.0f, 0.0f});
								Purple = 1;
							}
							if (i >= 4)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 125.0f + 150.0f * i, -100.0f, 0.0f });
								Purple = 0;
							}

							std::string AniName = "PurpleTile";
							AniName += std::to_string(Purple);
							Effect->ChangeAnimationState(AniName);
						}
						{
							std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{-350.0f - 150 * i, -100.0f, 0.0f});
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
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 350.0f + 150.0f * i, -100.0f, 0.0f });
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
							float4 EFfectPos = Effect->Transform.GetWorldPosition();
							if (i == 0)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -100.0f, -100.0f, 0.0f });
							}
							if (i == 1)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -250.0f, -100.0f, 0.0f });
							}
							if (i >= 2 && i < 4)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -125.0f - 150.0f * i, -100.0f, 0.0f });
								Purple = 1;
							}
							if (i >= 4)
							{
								Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -125.0f - 150.0f * i, -100.0f, 0.0f });
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


	{
		Skill Skill3;
		Skill3.IsControll = false;

		for (int i = 0; i < 1; i++)
		{
			Skill3.StateTest.CreateState(i, {
				.Start =
				[=](class GameEngineState* _Parent)
				{
					if (CurSkill->SkillUseDir == ActorDir::Right)
					{
						{
							std::shared_ptr<BossSkillBall> Effect = this->GetLevel()->CreateActor<BossSkillBall>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 200.0f, 30.0f, 0.0f });
							Effect->SetDir(ActorDir::Right);
						}

						{
							std::shared_ptr<BossSkillBall> Effect = this->GetLevel()->CreateActor<BossSkillBall>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -200.0f , 30.0f, 0.0f});
							Effect->SetDir(ActorDir::Left);
						}
					}


					if (CurSkill->SkillUseDir == ActorDir::Left)
					{
						{
							std::shared_ptr<BossSkillBall> Effect = this->GetLevel()->CreateActor<BossSkillBall>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 200.0f , 30.0f, 0.0f });
							Effect->SetDir(ActorDir::Right);
						}

						{
							std::shared_ptr<BossSkillBall> Effect = this->GetLevel()->CreateActor<BossSkillBall>();
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -200.0f, 30.0f, 0.0f });
							Effect->SetDir(ActorDir::Left);
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

		Skill3.StateTest.CreateState(1, {
			.Start =
			[=](class GameEngineState* _Parent)
			{
					CurSkill = nullptr;
					BallAttack = false;
			} });

		SkillState['B'] = Skill3;
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

		if (PurpleAttack == true && pair.first == 'P')
		{
			Skill& UseSkill = pair.second;

			CurSkill = &UseSkill;
			CurSkill->SkillUsePos = JinHillaBoss::GetMainBoss()->Transform.GetWorldPosition();
			CurSkill->SkillUseDir = JinHillaBoss::GetMainBoss()->GetDir();
			UseSkill.StateTest.ChangeState(0);
			return true;
		}

		if (BallAttack == true && pair.first == 'B')
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

	if (_Value == 'B')
	{
		SkillState['B'];
		BallAttack = true;
		SkillUseCheck();
	}
}