
//#define UserLightOn


// ���ϸ�� �Լ����� ��ġ��Ű�� ���ؽ� ���̴��� ������ �ڿ� _VS�� ���δ�.
// �ǹ��ִ� ���ؽ� ���̴��̴�.
// WorldProjection
float4 ColorShader_VS( float4 pos : POSITION ) : SV_POSITION
{
//#ifdef UserLightOn
	
//#endif
	return pos;
}

float4 TestShader_VS(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}