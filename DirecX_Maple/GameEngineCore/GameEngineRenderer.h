#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"
#include "GameEngineMesh.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineRenderUnit.h"

// ���� : GameEngineRenderer���� Order�� ������ �Ǵ� ������ �ǹ��Ѵ�.
// �������� �������ִ� ������
// �ڵ带 ¥�ٺ��� �׳� ������ ����ü�� �̿��ؾ� �ϴ� ��찡 ��������.
// �������� ������Ʈ�ΰ� �����̴�.
// �׷��� �������� �ּҴ��� �������� ���� �߿��� ��Ҹ� ��Ƴ���
// ���� ����Ʈ�� ��ü�� �ǰ�
// �������ε� ����� �� ���� ������
// ������ ������ ���� ���̴�.
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;

public:
	// constructer destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator = (const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator = (GameEngineRenderer&& _Other) noexcept = delete;

	// �̰� ���� ���ٸ�
	// ī�޶��� ��쿡��
	// �̰� ������ ȣ��Ǿ� �մϴ�.
	// �ϳ��� �������� �������� ī�޶� �ٶ� �� �ִ�.
	// ���� �Űܴٴϴ� ������ �ƴϴ�.
	void SetViewCameraSelect(int _Order);

	// ��� ī�޶󿡼� ���� ����

	// ���� ���ִ� ī�޶� �ٲٰڴٴ�
	
	// ���ٶ󺸴� ��� ī�޶󿡼� ���� �����ϰ�,
	// _Order ī�޶�� �̵��ϴ°�.
	// void SetChangeViewCameraAllClear(int _Order);

	void SetRenderOrder(int _Order);

	template <typename EnumType>
	void SetRenderOrder(EnumType _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}

	void SetCameraOrder(ECAMERAORDER _Order)
	{
		SetCameraOrder(static_cast<int>(_Order));
	}

	void SetCameraOrder(int _Order);

	// Create_PushBack������ �ƴմϴ�.
	// 0�� ���� ������ ����ٰ� ġ�� 0��°�� ���� ������ ���������.
	// 8���� �ϸ� vector�� Ȯ��ǰ� 8��°�� ���� ������ ����� �ȴ�.
	std::shared_ptr<GameEngineRenderUnit> CreateAndFindRenderUnit(int _Index = 0);
	
	void SetMesh(std::string_view _Name, int _Index = 0);
	void SetMaterial(std::string_view _Name, int _Index = 0);
	
	GameEngineShaderResHelper& GetShaderResHelper(int _Index = 0);

protected:
	void Start();
	virtual void Render(class GameEngineCamera* _Camera, float _Delta);
	virtual void SetMaterialEvent(std::string_view _Name, int _Index = 0);


	//std::shared_ptr<class GameEngineInputLayOut> LayOut;
	//std::shared_ptr<class GameEngineMesh> Mesh;
	//std::shared_ptr<class GameEngineMaterial> Material;
	//GameEngineShaderResHelper ShaderResHelper;

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

private:
	class GameEngineCamera* Camera = nullptr;

};

