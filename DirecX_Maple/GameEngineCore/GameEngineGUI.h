#pragma once
#include "GameEngineObject.h"

class GameEngineGUIWindow : public GameEngineObjectBase
{
public:
	void Begin();
	void End();
	// ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

	virtual void OnGUI() = 0;
};

// Ό³Έν :
class GameEngineGUI
{
public:
	static void Start();
	static void Release();

	static void GUIRenderStart();
	static void GUiRenderEnd();

	// constrcuter destructer
	GameEngineGUI();
	~GameEngineGUI();

	// delete Function
	GameEngineGUI(const GameEngineGUI& _Other) = delete;
	GameEngineGUI(GameEngineGUI&& _Other) noexcept = delete;
	GameEngineGUI& operator=(const GameEngineGUI& _Other) = delete;
	GameEngineGUI& operator=(GameEngineGUI&& _Other) noexcept = delete;

protected:

private:

};

