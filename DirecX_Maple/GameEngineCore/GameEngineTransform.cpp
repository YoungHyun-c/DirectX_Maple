#include "PreCompile.h"
#include "GameEngineTransform.h"

// int ArrColFunction[6][6];
std::function<bool(const CollisionParameter& _Data)> ArrColFunction[static_cast<int>(ColType::MAX)][static_cast<int>(ColType::MAX)];

class InitColFunction
{
public:
	InitColFunction()
	{
		for (size_t Left = 0; Left < static_cast<size_t>(ColType::MAX); Left++)
		{
			for (size_t Right = 0; Right < static_cast<size_t>(ColType::MAX); Right++)
			{
				ArrColFunction[Left][Right] = [](const CollisionParameter& _Data)
				{
					MsgBoxAssert("아직 처리되지 않은 함수입니다.");
					return false;
				};
			}
		}

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingBox Left = _Data.Left.AABB;
			Left.Center.z = 0.0f;
			DirectX::BoundingBox Right = _Data.Right.AABB;
			Right.Center.z = 0.0f;
			return Left.Intersects(_Data.Right.AABB);
		};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingBox Left = _Data.Left.AABB;
			Left.Center.z = 0.0f;
			DirectX::BoundingSphere Right = _Data.Right.SPHERE;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingBox Left = _Data.Left.AABB;
			Left.Center.z = 0.0f;
			DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingSphere Left = _Data.Left.SPHERE;
			Left.Center.z = 0.0f;
			DirectX::BoundingBox Right = _Data.Right.AABB;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingSphere Left = _Data.Left.SPHERE;
			Left.Center.z = 0.0f;
			DirectX::BoundingSphere Right = _Data.Right.SPHERE;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingSphere Left = _Data.Left.SPHERE;
			Left.Center.z = 0.0f;
			DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
			Left.Center.z = 0.0f;
			DirectX::BoundingBox Right = _Data.Right.AABB;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
			Left.Center.z = 0.0f;
			DirectX::BoundingSphere Right = _Data.Right.SPHERE;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
			Left.Center.z = 0.0f;
			DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};
	}
};

InitColFunction Inst;

GameEngineTransform::GameEngineTransform()
{

}

GameEngineTransform::~GameEngineTransform()
{

}

void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;

	// World Local

	// position
	// 부모
	// 100, 100
	// 나도
	// 100, 100
	// 나의 Local 100, 100
	// 나의 World 200, 200

	// SetWorldPosition(300, 300) 지금 내가 어디에 있건
	// 나의 위치가 300, 300으로 고정된다는것. 그치만 위치를 바꾸고, 부모를 따라다니게 만드려함.

	// 단순하게 생각해보면 부모의 위치에서 나의 위치를 빼면
	// 회전하고

	if (nullptr != Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix;

		// 나는 부모의 행렬을 곱해서 나의 행렬이 나오게 되었다.
		// 기존의 요소들은 유지해

		if (true == AbsoluteScale || true == AbsoluteRotation || true == AbsolutePosition)
		{
			// 수치를 고정시키려는 명령이 내려왔다.
			float4 WScale, WRotation, WPosition;
			float4 LScale, LRotation, LPosition;

			TransData.WorldMatrix.Decompose(WScale, WRotation, WPosition);

			if (true == AbsoluteScale)
			{
				WScale = TransData.Scale;
			}

			if (true == AbsoluteRotation)
			{
				WRotation = TransData.Rotation.EulerToQuaternion();
			}

			if (true == AbsolutePosition)
			{
				WPosition = TransData.Position;
			}

			TransData.WorldMatrix.Decompose(WScale, WRotation, WPosition);
			TransData.LocalWorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix.InverseReturn();
		}
	}

	// 내부에서 디컴포즈를 해주기 때문에
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldRotation, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();

	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();

	// 반지름
	ColData.OBB.Extents = TransData.WorldScale.ToABS().Half().Float3;
	ColData.OBB.Center = TransData.WorldPosition.Float3;
	ColData.OBB.Orientation = TransData.WorldQuaternion.Float4;
	//트랜스폼도 업데이트가 되었음


	// 월드 크기
	// 월드 회전
	// 월드 위치
	//ransData.WorldMatrix

	//TransData.WorldMatrix <= 내부에서
	
	// 로컬이랑 월드를 계산한적이 없어요.

	//ColData.AABB

	CalChilds();

	AbsoluteScale = false;
	AbsoluteRotation = false;
	AbsolutePosition = false;
}

void GameEngineTransform::CalculationViewAndProjection(const TransformData& _Transform)
{
	CalculationViewAndProjection(_Transform.ViewMatrix, _Transform.ProjectionMatrix);
}

void GameEngineTransform::CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection)
{
	TransData.ViewMatrix = _View;
	TransData.ProjectionMatrix = _Projection;
	TransData.WorldViewProjectionCalculation();
}

void GameEngineTransform::CalChilds()
{
	if (0 == Childs.size())
	{
		return;
	}

	for (GameEngineTransform* Trans : Childs)
	{
		Trans->TransformUpdate();
	}
}

bool GameEngineTransform::Collision(const CollisionParameter& _Data)
{
	return ArrColFunction[_Data.GetLeftTypeToInt()][_Data.GetRightTypeToInt()](_Data);
}