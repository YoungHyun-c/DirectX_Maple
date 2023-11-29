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
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel);

private:
	float Time = 0.0f;
	float LimitTime = 0.5f;
	// 스킬 만들기관련
	float4 PlayerPos = float4::ZERO;
	float4 CurPlayerPos = float4::ZERO;
	std::shared_ptr<class GameEngineSpriteRenderer> AnimationRenderer;
	std::function<void(AdeleSkill&)> UpdateFunc = nullptr;
	void SetSkillActor(const std::string_view& _SkillName, bool isRePlay = true);
	void SetSkillAnimation();
	void SetUpdateFunc();
	std::string SkillName;
	bool isRePlay = false;

	float BackSkillPosZ = static_cast<float>(DeepBufferType::BackSkill);
	float FrontSkillPosZ = static_cast<float>(DeepBufferType::FrontSkill);

	float4 Dir = float4::ZERO;
	// 스킬이름, 스킬
	std::shared_ptr<class GameEngineSpriteRenderer> DoubleJumpRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> UpJumpRenderer;
	void DoubleJump();
	void BoltJump();

	//// 디바이드
	//std::shared_ptr<class GameEngineSpriteRenderer> Divide1;
	//std::shared_ptr<class GameEngineSpriteRenderer> Divide2;
	//std::shared_ptr<class GameEngineSpriteRenderer> Divide3;
	//void DivideSkill();
	//std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	//std::shared_ptr<GameEngineCollision> AttackCol;
	//void AttackEvent();

	// 크리에이션
	std::shared_ptr<class GameEngineSpriteRenderer> Creation1;
	std::shared_ptr<class GameEngineSpriteRenderer> Creation2;
	std::shared_ptr<class GameEngineSpriteRenderer> Creation3;

	// 샤드
	std::list<std::vector<std::shared_ptr<class GameEngineSpriteRenderer>>*> Shard;
	std::list<std::vector<std::shared_ptr<GameEngineCollision>>*> ShardCollist;
	std::shared_ptr<GameEngineCollision> ShardCol;
	std::shared_ptr<class GameEngineSpriteRenderer> ShardImage;
	std::shared_ptr<class GameEngineSpriteRenderer> ShardEffect;
	void ShardSkill();
	bool ShradAppear = false;
	float ShardSpeed = 900.0f;

	// 임페일
	std::shared_ptr<class GameEngineSpriteRenderer> ImpaleA;
	std::shared_ptr<class GameEngineSpriteRenderer> ImpaleB;
	std::shared_ptr<class GameEngineSpriteRenderer> ImpaleE;
	void ImpaleSkill();

	// 레조넌스
	std::shared_ptr<class GameEngineSpriteRenderer> LesonensPrePare;
	std::shared_ptr<class GameEngineSpriteRenderer> LesonensEffect;
	std::shared_ptr<class GameEngineSpriteRenderer> LessonensEnd;
	std::shared_ptr<class GameEngineSpriteRenderer> LessonensBack;
	void LesonensSkill();

	//루인
	std::shared_ptr<class GameEngineSpriteRenderer> Ruin;
	void RuinSkill();


	//6차
	std::shared_ptr<class GameEngineSpriteRenderer> Maestro;
	void MaestroSkill();
};