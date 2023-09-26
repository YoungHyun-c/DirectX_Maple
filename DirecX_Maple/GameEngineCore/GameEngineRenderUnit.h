#pragma once
#include "GameEngineShaderResHelper.h"

// 설명 :
// 렌더링의 최소단위
// 이녀석을 돌리면 렌더링이 된다.
// final <- 더이상 상속 못 내린다.
class GameEngineRenderUnit final : public GameEngineObject, std::enable_shared_from_this<GameEngineRenderUnit>
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

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

	void ResSetting();
	void Draw();

	void SetParentRenderer(class GameEngineRenderer* _Renderer)
	{
		ParentRenderer = _Renderer;
	}

	class GameEngineRenderer* GetParentRenderer()
	{
		return ParentRenderer;
	}

	GameEngineShaderResHelper ShaderResHelper;

private:
	class GameEngineRenderer* ParentRenderer;

	// 최적화 대상이 될 수 있다.
	// 이걸 어떻게든 관리할 방법을 찾는게 맞다. (하나만 만들어서 돌려쓰면 안될지?)
	std::shared_ptr<class GameEngineInputLayOut> LayOut = nullptr;

	std::shared_ptr<class GameEngineMesh> Mesh = nullptr;
	std::shared_ptr<class GameEngineMaterial> Material = nullptr;
};

