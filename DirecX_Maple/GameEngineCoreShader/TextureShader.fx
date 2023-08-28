#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct PixelOutPut
{
    // 피셀쉐이더에 보내는 역활
    float4 POSITION : SV_Position;
    float4 TEXCORRD : TEXCOORD;
};

// 파일명과 함수명을 일치시키고 버텍스 쉐이더면 무조건 뒤에 _VS를 붙인다.
// 의미있는 버텍스 쉐이더이다.
PixelOutPut TextureShader_VS(GameEngineVertex2D _Input)
{
    // 쉐이더 문법 모두 0인 자료형으로 초기화 하는 것.
    PixelOutPut Result = (PixelOutPut)0;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    Result.TEXCORRD = _Input.TEXCOORD;
    
    return Result;
}

// b 버퍼 14
// t 텍스처
// s 셈플러
// 둘의 슬롯은 공유되지 않는다.

// 보통 샘플러의 텍스처는 1쌍으로 사용되기 때문에
// 샘플러는 텍스처의 색상을 가져올때 보간을 해주거나 특수한 공식들을 내부에서
// 사용해주는 용도가 있다.
Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    // 이런 방식으로 사용하면 내가 직접 계산공식을 세워야한다.
    //DiffuseTex.Load(int3);
    
    // 샘플러의 설정에 의해서 dx가 알아서 계산해주는 방식으로 처리하는 것.
    float4 Color = DiffuseTex.Sample(Sampler, _Input.TEXCORRD.xy);
    // 블렌드 처리를 해줘야 배경 투명값을 제거 할 수 있다.
    // 일단은 배경값 0이하는 없애게 처리
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    // 안에서 사용하지 않으면 아예 존재하지 않는다.
    return Color;
}