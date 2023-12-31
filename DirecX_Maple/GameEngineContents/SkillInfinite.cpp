#include "PreCompile.h"
#include "SkillInfinite.h"

#include "SkillInfiniteActor.h"
#include "SkillOrderSummonActor.h"

SkillInfinite::SkillInfinite()
{

}

SkillInfinite::~SkillInfinite()
{

}

void SkillInfinite::Start()
{
	SkillFunction::Start();
	{
		{
			InfiFront = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
			InfiFront->CreateAnimation("Infinite_Start_Forward", "Infinite_Start_Forward", 0.05f);
			InfiFront->CreateAnimation("Infinite_Loop_Forward", "Infinite_Loop_Forward", 0.1f);
			InfiFront->CreateAnimation("Infinite_End_Forward", "Infinite_End_Forward", 0.1f);

			InfiFront->Transform.SetLocalPosition({ 0.0f, 0.0f });
			InfiFront->AutoSpriteSizeOn();
			InfiFront->SetAutoScaleRatio(2);

			InfiFront->SetEndEvent("Infinite_Start_Forward", [&](GameEngineRenderer* _Renderer)
				{
					InfiFront->ChangeAnimation("Infinite_Loop_Forward");
				});

			InfiFront->SetEndEvent("Infinite_End_Forward", [&](GameEngineRenderer* _Renderer)
				{
					InfiFront->Off();
				});

			InfiFront->Off();

		}

		InfiBack = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Infi);
		InfiBack->CreateAnimation("Infinite_Start_Back", "Infinite_Start_Back", 0.1f);
		InfiBack->CreateAnimation("Infinite_Loop_Back", "Infinite_Loop_Back", 0.1f);
		InfiBack->CreateAnimation("Infinite_End_Back", "Infinite_End_Back", 0.1f);

		InfiBack->Transform.SetLocalPosition({ 0.0f, 0.0f });

		InfiBack->AutoSpriteSizeOn();
		InfiBack->SetAutoScaleRatio(2);

		InfiBack->SetEndEvent("Infinite_Start_Back", [&](GameEngineRenderer* _Renderer)
			{
				InfiBack->ChangeAnimation("Infinite_Loop_Back");
			});

		InfiBack->SetEndEvent("Infinite_End_Back", [&](GameEngineRenderer* _Renderer)
			{
				InfiBack->Off();
			});

		AllInfiniteActor.reserve(18);

		for (int i = 0; i < 9; i++)
		{
			InfiBack->SetFrameEvent("Infinite_Start_Back", i, [&](GameEngineSpriteRenderer* _Renderer)
				{
					CreateInfinite();
					CreateInfinite();
				});
		}

		InfiBack->SetFrameEvent("Infinite_Start_Back", 10, [&](GameEngineSpriteRenderer* _Renderer)
			{
				InfinitePosCal();
			});

		InfiBack->Off();
	}

}

void SkillInfinite::UseSkill()
{
	SkillFunction::UseSkill();

	UseFirst = true;

	InfiBack->ChangeAnimation("Infinite_Start_Back", true, 0);
	InfiBack->On();

	InfiFront->ChangeAnimation("Infinite_Start_Forward", true, 0);
	InfiFront->On();

	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	InfiTime = 0.0f;

	MapBgmName = GlobalValue::GetNeedGlobalValue()->GetCurBgmName();
	GlobalValue::GetNeedGlobalValue()->CurBgmStop();

	GameEngineSound::SoundPlay("Infinite.mp3");
	InfinitePlay = GameEngineSound::SoundPlay("5thAdelesOathInfinite.mp3");
}

void SkillInfinite::EndSkill()
{
	SkillFunction::EndSkill();

	InfiBack->ChangeAnimation("Infinite_End_Back");
	InfiFront->ChangeAnimation("Infinite_End_Forward");
	UseFirst = false;

	GlobalValue::GetNeedGlobalValue()->SetBgm(MapBgmName, 10);
}

void SkillInfinite::LevelEnd(GameEngineLevel* _NextLevel)
{
	InfinitePlay.Stop();
	Death();
}

void SkillInfinite::Update(float _Delta)
{
	Transform.SetWorldPosition(GetLevel()->GetMainCamera()->Transform.GetLocalPosition());

	InfiTime += _Delta;
	if (InfiTime >= InfiLimitTime && UseFirst == true)
	{
		InfiTime = 0.0f;
		InfinitePlay.Stop();
		EndSkill();
	}

}

void SkillInfinite::InfinitePosCal()
{
	for (size_t i = InfiniteCount; i < AllInfiniteActor.size(); i++)
	{
		InfiRandPos.SetSeed(time(nullptr));
		float RandPos = InfiRand;
		again:;
		int Rand = rand() % 3 + 1;
		InfiRand = static_cast<float>(InfiRandPos.RandomInt(10 , Rand * 30));
		InfiYRand = static_cast<float>(InfiRandPos.RandomInt(-10, Rand * 50));
		if (InfiRand == RandPos)
		{
			goto again;
		}

		AllInfiniteActor[i]->Transform.SetWorldPosition({ CurPlayerPos.X -400.0f + ((i % 18) * InfiRand),
			CurPlayerPos.Y + 3.0f * InfiYRand });

		AllInfiniteActor[i]->On();
	}
}

void SkillInfinite::CreateInfinite()
{
	std::shared_ptr<SkillInfiniteActor> _OrderActor = GetLevel()->CreateActor<SkillInfiniteActor>(ContentsObjectType::FrontSkill);
	CurInfiPos = _OrderActor->GetInfinitePos();
	AllInfiniteActor.push_back(_OrderActor);
}

void SkillInfinite::Release()
{
	SkillFunction::Release();
}