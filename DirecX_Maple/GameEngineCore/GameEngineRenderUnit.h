#pragma once
#include "GameEngineShaderResHelper.h"

// ���� :
// �������� �ּҴ���
// �̳༮�� ������ �������� �ȴ�.
// final <- ���̻� ��� �� ������.
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

	// ����ȭ ����� �� �� �ִ�.
	// �̰� ��Ե� ������ ����� ã�°� �´�. (�ϳ��� ���� �������� �ȵ���?)
	std::shared_ptr<class GameEngineInputLayOut> LayOut = nullptr;

	std::shared_ptr<class GameEngineMesh> Mesh = nullptr;
	std::shared_ptr<class GameEngineMaterial> Material = nullptr;
};

