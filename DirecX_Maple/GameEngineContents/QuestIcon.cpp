#include "PreCompile.h"
#include "Mouse.h"
#include "ChatManager.h"
#include "QuestIcon.h"

QuestIcon::QuestIcon()
{

}

QuestIcon::~QuestIcon()
{

}

void QuestIcon::LevelStart(GameEngineLevel* _PreveLevel)
{

}

void QuestIcon::Start()
{

}

void QuestIcon::Update(float _Delta)
{

}


void QuestIcon::PosUpdate()
{
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();

	QuestCol->Transform.SetLocalPosition({ PlayerPos.X , PlayerPos.Y + 50.0f});
}