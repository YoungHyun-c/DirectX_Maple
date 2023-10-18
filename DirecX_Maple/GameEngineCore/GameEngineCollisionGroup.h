#pragma once
#include <list>
#include <memory>
#include "GameEngineCollision.h"

// ���� :
class GameEngineCollisionGroup : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineCollisionGroup();
	~GameEngineCollisionGroup();

	// delete Function
	GameEngineCollisionGroup(const GameEngineCollisionGroup& _Other) = delete;
	GameEngineCollisionGroup(GameEngineCollisionGroup&& _Other) noexcept = delete;
	GameEngineCollisionGroup& operator=(const GameEngineCollisionGroup& _Other) = delete;
	GameEngineCollisionGroup& operator=(GameEngineCollisionGroup&& _Other) noexcept = delete;


	bool Collision(std::shared_ptr<GameEngineCollision> _Collision);

	bool Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos);

	bool Collision(std::shared_ptr<GameEngineCollision> _Collision, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function);

	bool Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function);

	bool CollisionEvent(std::shared_ptr<GameEngineCollision> _Collision, const EventParameter& _Event);

protected:
	void AllReleaseCheck() override;

private:
	void PushCollision(std::shared_ptr<class GameEngineCollision> _Collision);

	std::list<std::shared_ptr<class GameEngineCollision>> Collisions;
};

