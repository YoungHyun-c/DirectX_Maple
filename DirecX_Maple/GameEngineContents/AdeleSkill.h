#pragma once
#include "BasicFunction.h"
#include <functional>

class GameEngineSpriteRenderer;
class AdeleSkill : public BasicFunction
{
	friend class Player;
public:
	// constructer destructer
	AdeleSkill();
	~AdeleSkill();

	// delete Function
	AdeleSkill(const AdeleSkill& _Other) = delete;
	AdeleSkill(AdeleSkill&& _Other) noexcept = delete;
	AdeleSkill& operator = (const AdeleSkill& _Other) = delete;
	AdeleSkill& operator = (AdeleSkill&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	// 스킬 만들기관련
	float4 PlayerPos = float4::ZERO;
	std::shared_ptr<class GameEngineSpriteRenderer> AnimationRenderer;
	std::function<void(AdeleSkill&)> UpdateFunc = nullptr;
	void SetSkillActor(const std::string_view& _SkillName, bool isRePlay = true);
	void SetSkillAnimation();
	void SetUpdateFunc();
	std::string SkillName;
	bool isRePlay = false;


	// 스킬이름, 스킬
	std::shared_ptr<class GameEngineSpriteRenderer> DoubleJumpRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> UpJumpRenderer;
	void DoubleJump();
	void BoltJump();

	std::shared_ptr<class GameEngineSpriteRenderer> Divide1;
	std::shared_ptr<class GameEngineSpriteRenderer> Divide2;
	std::shared_ptr<class GameEngineSpriteRenderer> Divide3;
	void DivideSkill();

	std::shared_ptr<class GameEngineSpriteRenderer> Creation1;
	std::shared_ptr<class GameEngineSpriteRenderer> Creation2;
	std::shared_ptr<class GameEngineSpriteRenderer> Creation3;
};