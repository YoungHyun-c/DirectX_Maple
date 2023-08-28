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

// ���ϸ�� �Լ����� ��ġ��Ű�� ���ؽ� ���̴��� ������ �ڿ� _VS�� ���δ�.
// �ǹ��ִ� ���ؽ� ���̴��̴�.
PixelOutPut TextureShader_VS(GameEngineVertex2D _Input)
{
    // ���̴� ���� ��� 0�� �ڷ������� �ʱ�ȭ �ϴ� ��.
    PixelOutPut Result = (PixelOutPut)0;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    Result.TEXCORRD = _Input.TEXCOORD;
    
    return Result;
}

// b ���� 14
// t �ؽ�ó
// s ���÷�
// ���� ������ �������� �ʴ´�.

// ���� ���÷��� �ؽ�ó�� 1������ ���Ǳ� ������
// ���÷��� �ؽ�ó�� ������ �����ö� ������ ���ְų� Ư���� ���ĵ��� ���ο���
// ������ִ� �뵵�� �ִ�.
Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    // �̷� ������� ����ϸ� ���� ���� �������� �������Ѵ�.
    //DiffuseTex.Load(int3);
    
    // ���÷��� ������ ���ؼ� dx�� �˾Ƽ� ������ִ� ������� ó���ϴ� ��.
    float4 Color = DiffuseTex.Sample(Sampler, _Input.TEXCORRD.xy);
    // ���� ó���� ����� ��� ������ ���� �� �� �ִ�.
    // �ϴ��� ��氪 0���ϴ� ���ְ� ó��
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    // �ȿ��� ������� ������ �ƿ� �������� �ʴ´�.
    return Color;
}