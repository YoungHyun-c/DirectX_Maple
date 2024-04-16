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
		BossSkill[SkillsName::GreenSkill];
		BossSkill[SkillsName::PurPleSkill];
		BossSkill[SkillsName::BallSkill];
	}

	{
		CreateGreenSkill();
		CreatePurpleSkill();
		CreateBallSkill();
	}
}

void BossSkillManager::Update(float _Delta)
{
	if (nullptr == CurSkill)
	{
		return;
	}
	else
	{
		if (CurSkill->SkillControl == false)
		{
			CurSkill->Update(_Delta);
		}
	}
}

bool BossSkillManager::SkillUseCheck()
{
	if (nullptr != CurSkill)
	{
		return false;
	}

	for (std::pair<const SkillsName, Skills>& _Pair : BossSkill)
	{
		if (_Pair.first == SkillNameValue)
		{
			Skills& UseSkill = _Pair.second;
	
			CurSkill = &UseSkill;
			CurSkill->SkillUsePos = JinHillaBoss::GetMainBoss()->Transform.GetWorldPosition();
			CurSkill->SkillUseDir = JinHillaBoss::GetMainBoss()->GetDir();
			UseSkill.SkillState.ChangeState(0);
			return true;
		}
	}

	return false;
}

void BossSkillManager::SkillUseKey(SkillsName _Name)
{
  	switch (_Name)
	{
	case GreenSkill:
		SkillNameValue = _Name;
		break;
	case PurPleSkill:
		SkillNameValue = _Name;
		break;
	case BallSkill:
		SkillNameValue = _Name;
		break;
	default:
		MsgBoxAssert("스킬이름이 잘 못 들어왔습니다.");
		break;
	}

	BossSkill[SkillNameValue];
	SkillUseCheck();
}

void BossSkillManager::CreateGreenSkill()
{
	Skills GreenSkill;
	GreenSkill.SkillControl = false;

	for (int i = 0; i < 6; i++)
	{
		GreenSkill.SkillState.CreateState(i, {
			.Start =
			[=](class GameEngineState* _Parent)
			{
				int GreenNum = 0;
				if (CurSkill->SkillUseDir == ActorDir::Right)
				{
					{
						std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
						Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{400.0f + 150 * i, -100.0f, 0.0f});
						float4 EFfectPos = Effect->Transform.GetWorldPosition();
						if (i >= 1)
						{
							GreenNum = 1;
						}
						if (i >= 3)
						{
							GreenNum = 2;
						}

						std::string AniName = "GreenTile";
						AniName += std::to_string(GreenNum);
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
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -230.0f - 200.0f * (i - 1), -100.0f, 0.0f});
							GreenNum = 1;
						}
						if (i >= 3)
						{
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -200.0f - 150 * i, -100.0f, 0.0f });
							GreenNum = 2;
						}
						std::string AniName = "GreenTile";
						AniName += std::to_string(GreenNum);
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
							GreenNum = 1;
						}
						if (i >= 3)
						{
							GreenNum = 2;
						}

						std::string AniName = "GreenTile";
						AniName += std::to_string(GreenNum);
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
							GreenNum = 1;
						}
						if (i >= 3)
						{
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 200.0f + 150 * i, -100.0f, 0.0f });
							GreenNum = 2;
						}

						std::string AniName = "GreenTile";
						AniName += std::to_string(GreenNum);
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
	GreenSkill.SkillState.CreateState(6, {
		.Start =
		[&](class GameEngineState* _Parent)
		{
				CurSkill = nullptr;
				GreenSkill.SkillControl = true;
		} });

	BossSkill[SkillsName::GreenSkill] = GreenSkill;
}
void BossSkillManager::CreatePurpleSkill()
{
	Skills Purple;
	Purple.SkillControl = false;

	for (int i = 0; i < 6; i++)
	{
		Purple.SkillState.CreateState(i, {
			.Start =
			[=](class GameEngineState* _Parent)
			{
				int PurpleNum = 2;
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
							PurpleNum = 1;
						}
						if (i >= 4)
						{
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ 125.0f + 150.0f * i, -100.0f, 0.0f });
							PurpleNum = 0;
						}

						std::string AniName = "PurpleTile";
						AniName += std::to_string(PurpleNum);
						Effect->ChangeAnimationState(AniName);
					}
					{
						std::shared_ptr<BossSkillEffect> Effect = this->GetLevel()->CreateActor<BossSkillEffect>();
						Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{-350.0f - 150 * i, -100.0f, 0.0f});
						float4 EFfectPos = Effect->Transform.GetWorldPosition();
						if (i >= 2)
						{
							PurpleNum = 1;
						}
						if (i >= 4)
						{
							PurpleNum = 0;
						}

						std::string AniName = "PurpleTile";
						AniName += std::to_string(PurpleNum);
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
							PurpleNum = 1;
						}
						if (i >= 4)
						{
							PurpleNum = 0;
						}

						std::string AniName = "PurpleTile";
						AniName += std::to_string(PurpleNum);
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
							PurpleNum = 1;
						}
						if (i >= 4)
						{
							Effect->Transform.SetWorldPosition(CurSkill->SkillUsePos + float4{ -125.0f - 150.0f * i, -100.0f, 0.0f });
							PurpleNum = 0;
						}

						std::string AniName = "PurpleTile";
						AniName += std::to_string(PurpleNum);
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
	Purple.SkillState.CreateState(6, {
		.Start =
		[&](class GameEngineState* _Parent)
		{
				CurSkill = nullptr;
				Purple.SkillControl = true;
		} });
	BossSkill[SkillsName::PurPleSkill] = Purple;
}
void BossSkillManager::CreateBallSkill()
{
	{
		Skills BallSkill;
		BallSkill.SkillControl = false;

		for (int i = 0; i < 1; i++)
		{
			BallSkill.SkillState.CreateState(i, {
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

		BallSkill.SkillState.CreateState(1, {
			.Start =
			[&](class GameEngineState* _Parent)
			{
					CurSkill = nullptr;
					BallSkill.SkillControl = true;
			} });

		BossSkill[SkillsName::BallSkill] = BallSkill;
	}
}