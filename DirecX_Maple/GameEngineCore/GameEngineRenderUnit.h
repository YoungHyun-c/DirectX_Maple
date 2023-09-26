#pragma once

// 설명 :
// 렌더링의 최소단위
// 이녀석을 돌리면 렌더링이 된다.
class GameEngineRenderUnit : public GameEngineObject
{
public:
	// constructer destructer
	GameEngineRenderUnit();
	~GameEngineRenderUnit();

	// delete Function
	GameEngineRenderUnit(const GameEngineRenderUnit& _Other) = delete;
	GameEngineRenderUnit(GameEngineRenderUnit&& _Other) noexcept = delete;
	GameEngineRenderUnit& operator = (const GameEngineRenderUnit& _Other) = delete;
	GameEngineRenderUnit& operator = (GameEngineRenderUnit&& _Other) noexcept = delete;

protected:

private:
	//std::shared_ptr<class GameEngineInputLayOut> LayOut;
	//std::shared_ptr<class GameEngineMesh> Mesh;
	//std::shared_ptr<class GameEngineMaterial> Material;
	//GameEngineShaderResHelper ShaderResHelper;
};

