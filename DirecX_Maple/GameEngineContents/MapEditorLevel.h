#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineGUI.h>

// ���� :
class MapEditorLevel : public GameEngineLevel
{
public:
	// constructer destructer
	MapEditorLevel();
	~MapEditorLevel();

	// delete Function
	MapEditorLevel(const MapEditorLevel& _Other) = delete;
	MapEditorLevel(MapEditorLevel&& _Other) noexcept = delete;
	MapEditorLevel& operator = (const MapEditorLevel& _Other) = delete;
	MapEditorLevel& operator = (MapEditorLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

};

