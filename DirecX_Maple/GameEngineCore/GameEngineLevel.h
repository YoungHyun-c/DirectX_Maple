#pragma once
#include "GameEngineObject.h"

// 설명 :
// class GameEngineActor; 이렇게 전방선언 해도 되고
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;
	friend class GameEngineCamera;
public:
	// constructer destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator = (const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator = (GameEngineLevel&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineCamera> CreateCamera(int _Order, int _CameraOrder);

	template<typename ObjectType, typename EnumType>
	std::shared_ptr<ObjectType> CreateActor(EnumType _Order)
	{
		return CreateActor<ObjectType>(static_cast<int>(_Order));
	}

	template<typename ObjectType>
	std::shared_ptr<ObjectType> CreateActor(int _Order = 0)
	{
		std::shared_ptr<class GameEngineActor> NewChild = std::make_shared<ObjectType>();

		ActorInit(NewChild, _Order);

		// GameEngineObject 형으로 사용하고 있다면
		// 내가 잘못 형변환하면 Monster 였는데? Player <= 미친듯한 메모리크러시를 일으킨다.
		// 이녀석은 문제가 이유를 알 수 없게 터진다
		// 이 포인터가 상속관계에 있고 가상함수 테이블을 가지고 있다면
		// dynamic_cast를 통해서 안전하게 형변환이 가능하다
		// std::shared_ptr 진짜 포인터는 아니기 때문에 dynamic_cast 해야할 상황에서
		// 아래와 같은 함수를 사용하면 된다.
		return std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	std::shared_ptr<GameEngineCamera> GetMainCamera()
	{
		return Cameras[0];
	}

	std::shared_ptr<GameEngineCamera> GetCamera(int _Select)
	{
		return Cameras[_Select];
	}

protected:

private:
	// LevelChange가 벌어질때
	// 내가 다음 레벨이면 LevelStart
	// 내가 그럼 End하고 넘김
	// 내가 지금현재 레벨이 되면 호출
	virtual void LevelStart(GameEngineLevel* _PrevLevel){}
	// 내가 이제 다른 레벨로 이전하면 호출
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

	// 엑터 관련 기능들
	void AllUpdate(float _Delta) override;

	//void Render(float _Delta);

	void Release() override;

	void AllReleaseCheck() override;

	void ActorInit(std::shared_ptr<class GameEngineActor> _Actor, int _Order);

	void Render(float _Delta);

	// 이미 엑터가 child로 관리하고 있지만
	// 따로 카메라도 들고 있을 것이다.
	std::map<int, std::shared_ptr<class GameEngineCamera>> Cameras;

	// 이렇게도 전방선언 할 수 있다.
	// 근데 모든 클래스가 Object에 종속되어있다면 이렇게 안해도 되지 않을까 해서 주석
	//std::map<int, std::list<std::shared_ptr<class GameEngineActor>>> AllActors;
};

