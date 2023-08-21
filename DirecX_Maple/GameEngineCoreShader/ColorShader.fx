// 파일명과 함수명을 일치시키고 버텍스 쉐이더면 무조건 뒤에 _VS를 붙인다.
// 의미있는 버텍스 쉐이더이다.
// WorldProjection
float4 ColorShader_VS( float4 pos : POSITION ) : SV_POSITION
{

	return pos;
}

float4 ColorShader_PS(float4 pos : SV_Position) : SV_Target0
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}