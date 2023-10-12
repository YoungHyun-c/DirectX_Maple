//#pragma once
//#include "MonsterFunction.h"
//
//// Ό³Έν :
//class GhostDamien : public MonsterFunction
//{
//public:
//	static GhostDamien* SummonDamien;
//public:
//	// constructer destructer
//	GhostDamien();
//	~GhostDamien();
//
//	// delete Function
//	GhostDamien(const GhostDamien& _Other) = delete;
//	GhostDamien(GhostDamien&& _Other) noexcept = delete;
//	GhostDamien& operator = (const GhostDamien& _Other) = delete;
//	GhostDamien& operator = (GhostDamien&& _Other) noexcept = delete;
//
//protected:
//	void Start();
//	void Update(float _Delta) override;
//
//	void DeathUpdate(float _Delat) override;
//	void StandUpdate(float _Delta) override;
//
//private:
//	float MoveSpeed = 70.0f;
//	float SlideSpeed = 200.0f;
//	int Hp = 18688692000;
//	int Defense = 300;
//	float LeftCheck = 100.0f;
//	float RightCheck = 1750.0f;
//
//	std::shared_ptr<class GameEngineSpriteRenderer> HitEffect;
//
//};
//
