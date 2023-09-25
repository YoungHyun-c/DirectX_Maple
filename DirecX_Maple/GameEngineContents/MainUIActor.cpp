#include "PreCompile.h"
#include "MainUIActor.h"

MainUIActor::MainUIActor()
{

}

MainUIActor::~MainUIActor()
{

}

void MainUIActor::Start()
{
	AtereGage = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	AtereGage->SetImageScale({ 300, 50 });
}

void MainUIActor::Update(float _Delta)
{

}