#pragma once

// Ό³Έν :
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

	std::shared_ptr<GameEngineActor> BackGroundActor;
	std::shared_ptr<GameEngineSpriteRenderer> BackGroundRenderer;
	std::shared_ptr<GameEngineActor> BackDebugActor;
	std::shared_ptr<GameEngineSpriteRenderer> BackDebugRenderer;

	void SwitchMap();

protected:
	void Start() override;
	
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	bool SwitchRenderValue = true;
	std::shared_ptr<class Mouse> MouseObject;

};

