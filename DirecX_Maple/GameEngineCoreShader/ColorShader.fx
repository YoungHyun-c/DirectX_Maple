//#include "Transform.fx"

float4 ColorShader_VS(float4 pos : POSITION) : SV_Position
{
    return pos /* * WorldviewProjection */;
    // mul¿∫ Multiply
    //return mul(pos, worldViewProjectionMatrx);
}

float4 ColorShader_PS(float4 pos : SV_Position) : SV_Target0
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}