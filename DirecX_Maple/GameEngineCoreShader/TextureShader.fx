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
    Result.TEXCORRD.x = (_Input.TEXCOORD.x * Scale2DX) + Pos2Dx;
    Result.TEXCORRD.y = (_Input.TEXCOORD.y * Scale2DY) + Pos2DY;
    

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
    
    // �ȿ��� ������� ������ �ƿ� �������� �ʴ´�.
    return Color;
}