#pragma once
#include "GameEngineInputLayOut.h"
// Input LayOut이란 점 1개의 구조(특성)이다. (크기, 위치, 색 등등)

// 설명 : 얘가 버텍스 버퍼 정보를 제일 잘 알고 있어야 한다.
class GameEngineVertex2D
{
public:
	static GameEngineInputLayOutInfo VertexInfo;

	// 내가 얼마든지 바꿀 수 있는 것들이다.
public:
	float4 POSITION;
	float4 COLOR;
};

//struct Vertex
//{
//	float4 Pos0 : POSITION0;
//	float4 Pos1 : POSITION1;
//	float4 COLOR : COLOR;
//	float4 COLOR : TEXCOORD;
//};

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