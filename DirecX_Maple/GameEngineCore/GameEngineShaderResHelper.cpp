#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"

void GameEngineConstantBufferSetter::Setting()
{

}

void GameEngineConstantBufferSetter::Reset()
{

}

void GameEngineTextureSetter::Setting()
{

}

void GameEngineTextureSetter::Reset()
{

}

void GameEngineSamplerSetter::Setting()
{

}

void GameEngineSamplerSetter::Reset()
{

}

GameEngineShaderResHelper::GameEngineShaderResHelper()
{

}

GameEngineShaderResHelper::~GameEngineShaderResHelper()
{

}

void GameEngineShaderResHelper::ShaderResCheck(std::string _FunctionName, GameEngineShader* _Shader, ID3DBlob* _CompileCode)
{
	if (nullptr == _CompileCode)
	{
		MsgBoxAssert("컴파일 되지 않은 코드로는 쉐이더의 리소스를 조사할수가 없습니다.");
		return;
	}

	ID3DBlob* BinaryCode = _CompileCode;

	// 리플렉션을 통해서 얻어내는 것은 코드 그자체의 정보를 의미한다.
	// 클래스 개수
	// 함수
	// 클래스의 타입
	// 상속을 받았는지?
	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (S_OK != D3DReflect(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgBoxAssert("쉐이더 정보수집에 실패했습니다.");
		return;
	}

	D3D11_SHADER_DESC Info;

	// Info
	// 엔진 => 딸깍
	// 엔진에는 이미 갖춰진 데다가 + 노드가 된다. 언리얼 같은 경우에는
	CompileInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResDesc;
	// SetTexture("MyTexture" "AAAA.png");

	// 텍스처 쉐이더 샘플러 다 합쳐서 몇개냐?
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		// 텍스처를 10개 썼다. 10
		// 텍스처 2개 상수버퍼 3개 썼다.
		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		std::string UpperName = GameEngineString::ToUpperReturn(ResDesc.Name);

		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;
		//D3D_SIT_CBUFFER = 0,
		//D3D_SIT_TBUFFER = (D3D_SIT_CBUFFER + 1),
		//D3D_SIT_TEXTURE = (D3D_SIT_TBUFFER + 1),
		//D3D_SIT_SAMPLER = (D3D_SIT_TEXTURE + 1),
		//D3D_SIT_UAV_RWTYPED = (D3D_SIT_SAMPLER + 1),
		//D3D_SIT_STRUCTURED = (D3D_SIT_UAV_RWTYPED + 1),
		//D3D_SIT_UAV_RWSTRUCTURED = (D3D_SIT_STRUCTURED + 1),
		//D3D_SIT_BYTEADDRESS = (D3D_SIT_UAV_RWSTRUCTURED + 1),
		//D3D_SIT_UAV_RWBYTEADDRESS = (D3D_SIT_BYTEADDRESS + 1),
		//D3D_SIT_UAV_APPEND_STRUCTURED = (D3D_SIT_UAV_RWBYTEADDRESS + 1),
		//D3D_SIT_UAV_CONSUME_STRUCTURED = (D3D_SIT_UAV_APPEND_STRUCTURED + 1),
		//D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER = (D3D_SIT_UAV_CONSUME_STRUCTURED + 1),
		//D3D_SIT_RTACCELERATIONSTRUCTURE = (D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER + 1),
		//D3D_SIT_UAV_FEEDBACKTEXTURE = (D3D_SIT_RTACCELERATIONSTRUCTURE + 1),
		//D3D10_SIT_CBUFFER = D3D_SIT_CBUFFER,
		//D3D10_SIT_TBUFFER = D3D_SIT_TBUFFER,
		//D3D10_SIT_TEXTURE = D3D_SIT_TEXTURE,
		//D3D10_SIT_SAMPLER = D3D_SIT_SAMPLER,
		//D3D11_SIT_UAV_RWTYPED = D3D_SIT_UAV_RWTYPED,
		//D3D11_SIT_STRUCTURED = D3D_SIT_STRUCTURED,
		//D3D11_SIT_UAV_RWSTRUCTURED = D3D_SIT_UAV_RWSTRUCTURED,
		//D3D11_SIT_BYTEADDRESS = D3D_SIT_BYTEADDRESS,
		//D3D11_SIT_UAV_RWBYTEADDRESS = D3D_SIT_UAV_RWBYTEADDRESS,
		//D3D11_SIT_UAV_APPEND_STRUCTURED = D3D_SIT_UAV_APPEND_STRUCTURED,
		//D3D11_SIT_UAV_CONSUME_STRUCTURED = D3D_SIT_UAV_CONSUME_STRUCTURED,
		//D3D11_SIT_UAV_RWSTRUCTURED_WITH_COUNTER = D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC BufferDesc;
			BufferInfo->GetDesc(&BufferDesc);

			// 당연히 상수버퍼를 만들어야 한다.
			std::shared_ptr<GameEngineConstantBuffer> CBuffer = GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, UpperName, BufferDesc);

			_FunctionName;
			GameEngineConstantBufferSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			NewSetter.Res = CBuffer;
			NewSetter.Name = UpperName;
			NewSetter.BindPoint = ResDesc.BindPoint;

			ConstantBufferSetters.insert(std::make_pair(UpperName, NewSetter));

			break;
		}
		case D3D_SIT_TEXTURE:
		{
			std::shared_ptr<GameEngineTexture> Res
				= GameEngineTexture::Find("Nset.png");

			_FunctionName;
			GameEngineTextureSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			NewSetter.Res = Res;
			NewSetter.Name = UpperName;
			NewSetter.BindPoint = ResDesc.BindPoint;

			TextureSetters.insert(std::make_pair(UpperName, NewSetter));
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			std::shared_ptr<GameEngineSampler> Res
				= GameEngineSampler::Find("EngineBaseSampler");

			_FunctionName;
			GameEngineSamplerSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			NewSetter.Res = Res;
			NewSetter.Name = UpperName;
			NewSetter.BindPoint = ResDesc.BindPoint;

			SamplerSetters.insert(std::make_pair(UpperName, NewSetter));
			break;
		}
		default:
			break;
		}
	}

}