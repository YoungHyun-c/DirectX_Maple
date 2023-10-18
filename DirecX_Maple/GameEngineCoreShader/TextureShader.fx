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

// 상수버퍼를 만들때는 최대한
// 16바이트로 만드는게 좋다.
// 그래픽카드라는 것은 실수를 연산하기 위해서 만들어졌다.
// hlsl에서는 bool 같은건 사용하지 않는 것이 더 좋다.
cbuffer SpriteRendererInfo : register(b3)
{
    int FlipLeft = 0;
    int FlipUp = 0;
    float Temp1;
    float Temp2;
}

// 최적화는
// 횟수가 중요하다.

cbuffer SpriteData : register(b1)
{
    float Pos2Dx;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
}

// 파일명과 함수명을 일치시키고 버텍스 쉐이더면 무조건 뒤에 _VS를 붙인다.
// 의미있는 버텍스 쉐이더이다.
PixelOutPut TextureShader_VS(GameEngineVertex2D _Input)
{
    // 쉐이더 문법 모두 0인 자료형으로 초기화 하는 것.
    PixelOutPut Result = (PixelOutPut) 0;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    //Result.TEXCORRD = _Input.TEXCOORD;

    // 6의 버텍스가 들어올 것이다.
    float4 CalUV = _Input.TEXCOORD;
    
    // hlsl은 사용하지 않은 녀석은 인식하지 못한다.
    // 결과에 유의미한 영향을 주는 리소스가 아니면 hlsl은 최적화를 통해서 그 리소스를 배제한다.
    // 결과에 영향을 안주는 상수버퍼가 의미가 있어? 그런 상수버퍼는 내가 알아서 삭제할께.
    if (0 != FlipLeft)
    {
        CalUV.x *= -1;
        CalUV.x += 1;
    }
    
    if (0 != FlipUp)
    {
        CalUV.y *= -1;
        CalUV.y += 1;
        
    }
    
    Result.TEXCORRD.x = (CalUV.x * Scale2DX) + Pos2Dx;
    Result.TEXCORRD.y = (CalUV.y * Scale2DY) + Pos2DY;
    

    // 버텍스 들은 어떻게 되어있나?
    
    
    return Result;
}

// b 버퍼 14
// t 텍스처
// s 셈플러
// 둘의 슬롯은 공유되지 않는다.

// 보통 샘플러의 텍스처는 1쌍으로 사용되기 때문에
// 샘플러는 텍스처의 색상을 가져올때 보간을 해주거나 특수한 공식들을 내부에서
// 사용해주는 용도가 있다.

// 우리 규칙

cbuffer ColorData : register(b1)
{
    float4 PlusColor; // 최종색상에 더한다.
    float4 MulColor; // 최종색상에 곱한다.
}

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    // 이런 방식으로 사용하면 내가 직접 계산공식을 세워야한다.
    //DiffuseTex.Load(int3);
    
    // 샘플러의 설정에 의해서 dx가 알아서 계산해주는 방식으로 처리하는 것.
    // 스위즐링 문법
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCORRD.xy);
    // 블렌드 처리를 해줘야 배경 투명값을 제거 할 수 있다.
    // 일단은 배경값 0이하는 없애게 처리
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    Color += PlusColor;
    Color *= MulColor;
    
    if (0 >= Color.a)
    {
        Color.a = 0.0f;
    }
    
    // 안에서 사용하지 않으면 아예 존재하지 않는다.
    return Color;
}