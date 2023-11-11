#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineCollision;

class DropItem : public GameEngineActor
{
	friend class GlobalValue;
public:

	DropItem();
	~DropItem();

	DropItem(const DropItem& _Other) = delete;
	DropItem(DropItem&& _Other) noexcept = delete;
	DropItem& operator=(const DropItem& _Other) = delete;
	DropItem& operator=(DropItem&& _Other) noexcept = delete;

	void MoveDropItem(float _Delta);

	const std::string_view GetItemName()
	{
		return ItemName;
	}

	std::shared_ptr<GameEngineSpriteRenderer> GetRender()
	{
		return DropItemRender;
	}

	void SetQuadraticFunction(float _XDistance, float4 _StartPos, float _MaxY = 300.0f)
	{
		XDistance = _XDistance;
		Xintercept = XDistance + _StartPos.X;
		MaxY = _MaxY;
		MaxY += StartPos.Y;
		StartPos = _StartPos;

		if (Xintercept == 0.0f)
		{
			Xintercept = 1.0f;
		}

		if (XDistance >= 0)
		{
			Dir = 1.0f;
		}
		else
		{
			Dir = -1.0f;
		}

		float Num = (StartPos.X * Xintercept) - (((StartPos.X + Xintercept) / 2.0f) * ((StartPos.X + Xintercept) / 2.0f));
		Coefficient = MaxY / Num;

		Transform.SetLocalPosition(_StartPos);

		isFuncSet = true;
	}

	void SetDropItemInfo(const std::string_view& _ItemName, int _ItemType);
	void GetItem();

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> DropItemRender;
	std::shared_ptr<GameEngineCollision> DropItemCollision;

	std::shared_ptr<GameEngineTexture> ColMap;

	float4 StartPos = { 0, 0 };

	bool isFuncSet = false;
	bool isInfoSet = false;
	bool isGround = false;
	bool isGet = false;

	std::string ItemName = "";
	int ItemType = 0;

	float MaxY = 60.0f;

	float Xintercept = 0.0f;
	float XDistance = 0.0f;
	float Coefficient = 0.0f;

	float VerticalMoveCount = 0.0f;
	bool UpMove = true;
	bool DownMove = false;

	float Dir = 0.0f;
};

