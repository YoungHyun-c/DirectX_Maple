//#pragma once
//#include "MonsterFunction.h"
//
//// Ό³Έν :
//class GhostSwoo : public MonsterFunction
//{
//public:
//	static GhostSwoo* SummonSwoo;
//public:
//	// constructer destructer
//	GhostSwoo();
//	~GhostSwoo();
//
//	// delete Function
//	GhostSwoo(const GhostSwoo& _Other) = delete;
//	GhostSwoo(GhostSwoo&& _Other) noexcept = delete;
//	GhostSwoo& operator = (const GhostSwoo& _Other) = delete;
//	GhostSwoo& operator = (GhostSwoo&& _Other) noexcept = delete;
//
//protected:
//	void Start();
//	void Update(float _Delta) override;
//	
//	void DeathUpdate(float _Delta) override;
//
//
//private:
//	float MoveSpeed = 50.0f;
//	int Hp = 18688692000;
//	int Defense = 300;
//	float LeftCheck = 100.0f;
//	float RightCheck = 1750.0f;
//
//	std::shared_ptr<class GameEngineSpriteRenderer> BallSprite;
//};
//
