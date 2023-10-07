#pragma once
#include "BasicFunction.h"

// Ό³Έν :
class GameEngineSpriteRenderer;
class Mouse : public BasicFunction
{
public:
	// constructer destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator = (const Mouse& _Other) = delete;
	Mouse& operator = (Mouse&& _Other) noexcept = delete;

	static std::shared_ptr<Mouse> GetMouse()
	{
		return CurMouse;
	}

	std::shared_ptr<class GameEngineCollision> GetMouseCollision()
	{
		return CursorCollision;
	}

	void SetCurMouse(std::shared_ptr<Mouse> _Mouse)
	{
		CurMouse = _Mouse;
	}

	bool Click()
	{
		return IsClick;
	}

	bool DoubleClick()
	{
		return IsDoubleClick;
	}

	void ClickUpdate();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	static std::shared_ptr<Mouse> CurMouse;

	void PosUpdate();

	std::shared_ptr<class GameEngineUIRenderer> Cursor;
	std::shared_ptr<class GameEngineCollision> CursorCollision;

	bool IsClick = false;
	bool IsDoubleClick = false;

	float ClickCount = 0.0f;
	float DoubleClickCount = 0.0f;

};

