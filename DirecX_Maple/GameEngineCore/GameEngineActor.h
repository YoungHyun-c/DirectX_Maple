#pragma once
#include "GameEngineCoreObject.h"
#include <list>

// 설명 :
class GameEngineActor : public GameEngineCoreObject
{
	friend GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	template<typename ObjectType>
	std::shared_ptr<ObjectType> CreateComponent(int _Order = 0)
	{
		std::shared_ptr<class GameEngineComponent> NewChild = std::make_shared <ObjectType>();
		NewChild->SetParent(this);
		NewChild->Start();
		Childs[_Order].push_back(NewChild);

		return std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	class GameEngineLevel* GetLevel();

protected:

private:
	// 다형성은 무조건 위쪽을 가질수록 범용성이 높아진다.
	// 그리고 + 이런 기능은
	// Renderer와 Collision : GameEngineComponenet
};

