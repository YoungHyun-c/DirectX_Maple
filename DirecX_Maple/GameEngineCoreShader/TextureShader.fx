#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct PixelOutPut
{
    // �Ǽ����̴��� ������ ��Ȱ
    float4 POSITION : SV_Position;
    float4 TEXCORRD : TEXCOORD;
};

// ������۸� ���鶧�� �ִ���
// 16����Ʈ�� ����°� ����.
// �׷���ī���� ���� �Ǽ��� �����ϱ� ���ؼ� ���������.
// hlsl������ bool ������ ������� �ʴ� ���� �� ����.
cbuffer SpriteRendererInfo : register(b3)
{
    int FlipLeft = 0;
    int FlipUp = 0;
    float Temp1;
    float Temp2;
}

// ����ȭ��
// Ƚ���� �߿��ϴ�.

cbuffer SpriteData : register(b1)
{
    float Pos2Dx;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
}

// ���ϸ�� �Լ����� ��ġ��Ű�� ���ؽ� ���̴��� ������ �ڿ� _VS�� ���δ�.
// �ǹ��ִ� ���ؽ� ���̴��̴�.
PixelOutPut TextureShader_VS(GameEngineVertex2D _Input)
{
    // ���̴� ���� ��� 0�� �ڷ������� �ʱ�ȭ �ϴ� ��.
    PixelOutPut Result = (PixelOutPut) 0;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    //Result.TEXCORRD = _Input.TEXCOORD;

    // 6�� ���ؽ��� ���� ���̴�.
    float4 CalUV = _Input.TEXCOORD;
    
    // hlsl�� ������� ���� �༮�� �ν����� ���Ѵ�.
    // ����� ���ǹ��� ������ �ִ� ���ҽ��� �ƴϸ� hlsl�� ����ȭ�� ���ؼ� �� ���ҽ��� �����Ѵ�.
    // ����� ������ ���ִ� ������۰� �ǹ̰� �־�? �׷� ������۴� ���� �˾Ƽ� �����Ҳ�.
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
    

    // ���ؽ� ���� ��� �Ǿ��ֳ�?
    
    
    return Result;
}

// b ���� 14
// t �ؽ�ó
// s ���÷�
// ���� ������ �������� �ʴ´�.

// ���� ���÷��� �ؽ�ó�� 1������ ���Ǳ� ������
// ���÷��� �ؽ�ó�� ������ �����ö� ������ ���ְų� Ư���� ���ĵ��� ���ο���
// ������ִ� �뵵�� �ִ�.

// �츮 ��Ģ

cbuffer ColorData : register(b1)
{
    float4 PlusColor; // �������� ���Ѵ�.
    float4 MulColor; // �������� ���Ѵ�.
}

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    // �̷� ������� ����ϸ� ���� ���� �������� �������Ѵ�.
    //DiffuseTex.Load(int3);
    
    // ���÷��� ������ ���ؼ� dx�� �˾Ƽ� ������ִ� ������� ó���ϴ� ��.
    // ������ ����
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCORRD.xy);
    // ���� ó���� ����� ��� ������ ���� �� �� �ִ�.
    // �ϴ��� ��氪 0���ϴ� ���ְ� ó��
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
    
    // �ȿ��� ������� ������ �ƿ� �������� �ʴ´�.
    return Color;
}