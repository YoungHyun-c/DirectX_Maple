#include "PreCompile.h"
#include "FormerEffect.h"

FormerEffect::FormerEffect()
{

}

FormerEffect::~FormerEffect()
{

}

void FormerEffect::Start()
{
	{
		Former6thEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
		Former6thEffect->AutoSpriteSizeOn();
		Former6thEffect->CreateAnimation("FormerEffect", "FormerEffect", 0.1f, -1, -1, false);
		Former6thEffect->ChangeAnimation("FormerEffect");
		Former6thEffect->On();
	}
}

void FormerEffect::Update(float _Delta)
{
	if (true == Former6thEffect->IsCurAnimationEnd())
	{
		Former6thEffect->Off();
	}

	Former6thEffect->Transform.SetWorldPosition(GetLevel()->GetMainCamera()->Transform.GetLocalPosition());
}