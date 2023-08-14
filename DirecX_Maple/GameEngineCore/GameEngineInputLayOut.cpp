#include "PreCompile.h"
#include "GameEngineInputLayOut.h"

GameEngineInputLayOut::GameEngineInputLayOut()
{

}

GameEngineInputLayOut::~GameEngineInputLayOut()
{
	if (nullptr != LayOut)
	{
		LayOut->Release();
		LayOut = nullptr;
	}
}

void GameEngineInputLayOut::ResCreate()
{
	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, ���ؽ��� ��������
	// UINT NumElements, ���������� ����
	// const void* pShaderBytecodeWithInputSignature, // ���̴� �ڵ�
	// SIZE_T BytecodeLength, ���̴� �ڵ� ����
	// ID3D11InputLayOut** ppInputLayOut // �׷��� ������� ������

	// D3D11_INPUT_ELEMENT_DESC InputElementDescs[20];
	// pShaderBytecodeWithInputSignature ���̴� �ڵ� �޶�� �ϴ� ��

	// GameEngineCore::MainDevice.GetDevice()->CreateInputLayout(InputElementDescs, 20, &LayOut);
}

void GameEngineInputLayOut::Setting()
{
	if (nullptr == LayOut)
	{
		MsgBoxAssert("����������� ���� ���ؽ� ���۸� ������ ���� �����ϴ�.");
	}

	// ���ؽ� ���۸� ������ �־��� �� �ִ�.
	GameEngineCore::MainDevice.GetContext()->IASetInputLayout(LayOut);
}