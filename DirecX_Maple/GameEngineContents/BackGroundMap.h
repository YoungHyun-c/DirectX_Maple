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

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = DefaultGroundColor, std::string_view _DebugMapName ="");

	inline float4 GetMapScale()
	{
		return BackTexture->GetScale();
	}

	std::shared_ptr<class GameEngineTexture> GetColMap()
	{
		return BackColTexture;
	}

	void Init(const std::string& _FileName, const std::string& _DebugFileName);

	void SwitchRenderer();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	bool SwitchRenderValue = true;
	std::string FileName;
	std::string DebugFileName;

	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer;
	std::shared_ptr<class GameEngineUIRenderer> DarkRenderer;
	std::shared_ptr<class GameEngineTexture> BackTexture = nullptr;
	std::shared_ptr<class GameEngineTexture> BackColTexture = nullptr;

	std::shared_ptr<class Mouse> MouseObject;

	std::shared_ptr<class PotalManager> Potal = nullptr;
	std::shared_ptr<class RingPotalManager> RingPotal1 = nullptr;
	std::shared_ptr<class RingPotalManager> RingPotal2 = nullptr;
};

