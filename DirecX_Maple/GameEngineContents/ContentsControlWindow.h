#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class Tab
{
public:
	std::string Name;
	int Index;

	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) = 0;

	Tab(std::string_view _Name)
	{
		Name = _Name;
	}
};

class TestTab : public Tab
{
	// TestLevelMember
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTiame);

public:
	TestTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};

class MapEditorTab : public Tab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime)
	{

	}

public:
	MapEditorTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};


// ���� :
class ContentsControlWindow : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	void LevelChangeScreen(GameEngineLevel* _Level);
	
	std::shared_ptr<Tab> CurTab = nullptr;
	std::vector<std::shared_ptr<Tab>> Tabs;
};

