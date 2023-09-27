#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
};

struct PixelOutPut
{
    // 픽셀쉐이더에 보내는 역할
    float4 POSITION : SV_POSITION;
};

PixelOutPut DebugColor_VS(GameEngineVertex2D _Input)
{
    // 쉐이더 문법 모두 0인 자료형으로 초기화 하는 것
    PixelOutPut Result = (PixelOutPut) 0;    
    //Result.POSITION = _Input.POSITION;
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);

    return Result;
}

// 색깔 바꾸기
cbuffer DebugColor : register(b0)
{
    float4 Color;
}

float4 DebugColor_PS(PixelOutPut _Input) : SV_Target0
{
    // 빨간색.
    return Color;
}