#include "PreCompile.h"
#include "AtereSword.h"

AtereSword::AtereSword()
{

}

AtereSword::~AtereSword()
{

}

void AtereSword::Start()
{
	if (nullptr == GameEngineSprite::Find("AtereSword"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("UITexture");
		Dir.MoveChild("AtereSword");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	SwordAnimation = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	SwordAnimation->CreateAnimation("Appear", "Sword_Appear", 0.1f);
	SwordAnimation->CreateAnimation("End", "Sword_End", 0.1f);
	SwordAnimation->CreateAnimation("Loop", "Sword_Loop", 0.1f);
	SwordAnimation->AutoSpriteSizeOn();

	SwordAnimation->SetEndEvent("Appear", [&](GameEngineSpriteRenderer*)
		{
			SwordAnimation->ChangeAnimation("Loop");
			SwordAnimation->On();
		});

	SwordAnimation->SetEndEvent("End", [&](GameEngineSpriteRenderer*)
		{
			SwordAnimation->Off();
		});
	
	ChangeState(AtereSwordActor::Appear);
}

void AtereSword::Update(float _Delta)
{
	//StateUpdate(_Delta);
}

void AtereSword::ChangeState(AtereSwordActor _State)
{
	if (_State != SwordState)
	{
		switch (_State)
		{
		case AtereSwordActor::Appear:
			AppearStart();
			break;
		case AtereSwordActor::Loop:
			LoopStart();
			break;
		case AtereSwordActor::End:
			EndStart();
			break;
		case AtereSwordActor::Max:
		default:
			MsgBoxAssert("존재하지 않는 상태로 Sword를 시작하려했습니다.");
			break;
		}
	}

	SwordState = _State;
}

void AtereSword::AppearStart()
{
	SwordAnimation->ChangeAnimation("Appear");
	SwordAnimation->On();
}
void AtereSword::LoopStart()
{
	SwordAnimation->ChangeAnimation("Loop");
}
void AtereSword::EndStart()
{
	SwordAnimation->ChangeAnimation("End");
}

void AtereSword::AppearUpdate(float _Delta)
{
	if (SwordAnimation->IsCurAnimationEnd() == true)
	{
		ChangeState(AtereSwordActor::Loop);
		return;
	}
}
void AtereSword::LoopUpdate(float _Delta)
{
	if (SwordAnimation->IsCurAnimationEnd() == true)
	{
		ChangeState(AtereSwordActor::End);
		return;
	}
}
void AtereSword::EndUpdate(float _Delta)
{

}

void AtereSword::StateUpdate(float _Delta)
{
	switch (SwordState)
	{
	case AtereSwordActor::Appear:
		return AppearUpdate(_Delta);
	case AtereSwordActor::Loop:
		return LoopUpdate(_Delta);
	case AtereSwordActor::End:
		return EndUpdate(_Delta);
	case AtereSwordActor::Max:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Sword Update를 하려했습니다.");
		break;
	}
}

void AtereSword::LevelStart(GameEngineLevel* _PreveLevel)
{

}
void AtereSword::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}