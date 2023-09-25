#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"
#include "GameEngineMesh.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResHelper.h"

// 설명 : GameEngineRenderer에게 Order는 랜더링 되는 순서를 의미한다.
// 엔진에서 지원해주는 렌더링
// 코드를 짜다보면 그냥 렌더링 그자체를 이용해야 하는 경우가 많아진다.
// 렌더러가 컴포넌트인게 문제이다.
// 그래서 렌더링의 최소단위 렌더링에 가장 중요한 요소만 모아놓은
// 렌더 유니트가 주체가 되고
// 값형으로도 사용할 수 있을 정도로
// 간단한 구조를 가질 것이다.
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

	// 이걸 좀더 간다면
	// 카메라의 경우에는
	// 이게 무조건 호출되야 합니다.
	// 하나의 랜더러를 여러개의 카메라가 바라볼 수 있다.
	// 내가 옮겨다니는 개념이 아니다.
	void SetViewCameraSelect(int _Order);

	// 모든 카메라에서 나를 빼고

	// 나를 봐주는 카메라를 바꾸겠다는
	
	// 날바라보던 모든 카메라에서 나를 삭제하고,
	// _Order 카메라로 이동하는거.
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
	
	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

protected:
	void Start();
	virtual void Render(class GameEngineCamera* _Camera, float _Delta);

	void ResSetting();
	void Draw();

	std::shared_ptr<class GameEngineInputLayOut> LayOut;
	std::shared_ptr<class GameEngineMesh> Mesh;
	std::shared_ptr<class GameEngineMaterial> Material;
	GameEngineShaderResHelper ShaderResHelper;

	//std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

private:
	class GameEngineCamera* Camera = nullptr;

};

