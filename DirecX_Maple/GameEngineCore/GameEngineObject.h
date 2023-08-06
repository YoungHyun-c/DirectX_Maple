#pragma once
#include "GameEngineTransform.h"

// 우리 엔진의 가장 기본적인
// Start 이녀석이 시작 될때
// Update 이녀석이 업데이트될때
// Release 이녀석이 지워질때

// 설명 :
class GameEngineObject : public std::enable_shared_from_this<GameEngineObject>
{
	friend class GameEngineLevel;
	friend class GameEngineCore;

	;
public:
	GameEngineTransform Transform;

	// constructer destructer
	GameEngineObject();
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator = (const GameEngineObject& _Other) = delete;
	GameEngineObject& operator = (GameEngineObject&& _Other) noexcept = delete;

	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Release() {}

	virtual void On()
	{
		IsUpdateValue = true;
	}

	virtual void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		this->IsDeathValue = true;
	}

	virtual bool IsUpdate()
	{
		return Parent == nullptr ? true == IsUpdateValue && false == IsDeathValue : Parent->IsUpdate() && true == IsUpdateValue && false == IsDeathValue;
	}

	virtual bool IsDeath()
	{
		return Parent == nullptr ? IsDeathValue : Parent->IsDeathValue && IsDeathValue;
	}

	int GetUpdateOrder()
	{
		return UpdateOrder;
	}

	template<typename EnumType>
	void SetOreder(EnumType _Order)
	{
		SetUpdateOrder(static_cast<int>(_Order));
	}

	virtual void SetUpdateOrder(int _Order)
	{
		UpdateOrder = _Order;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	void SetName(const std::string& _Name)
	{
		Name = _Name;
	}

	std::string GetName()
	{
		return Name;
	}

	virtual void AllUpdate(float _Delta);

	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
		// Parent->Transform.SetParent(_Parent->Transform);
	}

	template<typename ParentType>
	void SetParent(std::shared_ptr<ParentType> _Parent)
	{
		Parent = _Parent.get();
		Transform.SetParent(_Parent->Transform);
		// Parent->Transform.SetParent(_Parent->Transform);
	}

	GameEngineObject* GetParentObject()
	{
		return Parent;
	}

	template<typename ParentType>
	ParentType* GetParent()
	{
		return dynamic_cast<ParentType*>(Parent);
	}

	template<typename ConvertType>
	std::shared_ptr<ConvertType> GetDynamic_Cast_This()
	{
		std::shared_ptr<GameEngineObject> ObjectPtr = shared_from_this();
		std::shared_ptr<ConvertType> CameraPtr = std::dynamic_pointer_cast<ConvertType>(ObjectPtr);

		if (nullptr == CameraPtr)
		{
			MsgBoxAssert("다이나믹 캐스트에 실패했습니다. 가상함수 테이블 부모가 누구인지 확인해보세요. 혹은 부모 생성자에서는 사용이 불가능한 함수입니다.");
		}
		
		return CameraPtr;
	}



	//template<typename ObjectType>
	//std::shared_ptr<ObjectType> CreateChild(int _Order = 0)
	//{
	//	std::shared_ptr<class GameEngineObject> NewChild = std::make_shared<ObjectType>();


	//	NewChild->Start();
	//	NewChild->Parent = this;
	//	Childs[_Order].push_back(NewChild);

	//	// GameEngineObject형으로 사용하고 있따면
	//	// 내가 잘못형변환하면 Monster였는데? Player <= 미친듯한 메모리 크러시를 일으킨다.
	//	// 이녀석은 문제가 이유를 알 수 없게 터진다.
	//	// 이 포인터가 상속관계 있고 가상함수 테이블을 가지고 있다면
	//	// dynamic_cast를 통해서 안전하게 형변환이 가능하다.
	//	// std::shared_ptr 진짜 포인터는 아니기 때문에 dynamic_cast 해야할 상황에서
	//	// 아래와 같은 함수를 사용하면 된다.
	//	return std::dynamic_pointer_cast<ObjectType>(NewChild);
	//}
	//
	//virtual void AllUpdate(float _Delta);

protected:
	GameEngineObject* Parent = nullptr;

	// 오더링을 위해서
	std::map<int, std::list<std::shared_ptr<class GameEngineObject>>> Childs;

private:


	std::string Name;
	float LiveTime = 0.0f;
	int UpdateOrder = 0;
	bool IsUpdateValue = true; // 이걸 false로 만들면 된다.
	bool IsDeathValue = false; // 아예 메모리에서 날려버리고 싶어.

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}
};

