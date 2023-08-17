#pragma once
#include "GameEngineInputLayOut.h"
// Input LayOut�̶� �� 1���� ����(Ư��)�̴�. (ũ��, ��ġ, �� ���)

// ���� : �갡 ���ؽ� ���� ������ ���� �� �˰� �־�� �Ѵ�.
class GameEngineVertex2D
{
public:
	static GameEngineInputLayOutInfo VertexInfo;

public:
	float4 POSITION;
	float4 COLOR;
};

class GameEngine3Dvertex
{
public:
	static GameEngineInputLayOutInfo VertexInfo;
public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
	float4 NORMAL;
	float4 BINORMAL;
	float4 TANGENT;
	float4 WEIGHT;
	int BLENDINDICES[4];
};