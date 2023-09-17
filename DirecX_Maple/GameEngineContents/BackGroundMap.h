#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BackGroundMap : public GameEngineActor
{
public:
	static BackGroundMap* MainMap;

public:
	// constructer destructer
	BackGroundMap();
	~BackGroundMap();

	// delete Function
	BackGroundMap(const BackGroundMap& _Other) = delete;
	BackGroundMap(BackGroundMap&& _Other) noexcept = delete;
	BackGroundMap& operator = (const BackGroundMap& _Other) = delete;
	BackGroundMap& operator = (BackGroundMap&& _Other) noexcept = delete;

	//GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

	void Init(const std::string& _FileName, const std::string& _DebugFileName);

	void SwitchRenderer();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool SwitchRenderValue = true;
	std::string FileName;

	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer;

};

