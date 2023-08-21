#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader()
{

}

GameEngineShader::~GameEngineShader()
{

}

void GameEngineShader::CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow)
{
	ShaderTypeValue = _Type;

	switch (_Type)
	{
	case ShaderType::None:
	{
		MsgBoxAssert("쉐이더 타입이 잘못들어왔습니다.");
		break;
	}
	case ShaderType::Vertex:
		Version = "vs";
		break;
	case ShaderType::Pixel:
		Version = "ps";
		break;
	case ShaderType::Max:
	{
		MsgBoxAssert("쉐이더 타입이 잘못들어왔습니다.");
		break;
	}
	default:
		break;
	}

	Version += "_";
	Version += std::to_string(_VersionHigh); // 5
	Version += "_";
	Version += std::to_string(_VersionLow); // 0

	// "vs_5_0"
}

// 부모가 자식클래스를 알고 있는 경우라 애매함
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"

bool GameEngineShader::AutoCompile(GameEngineFile& _File)
{
	// 쉐이더 파일안
	// 쉐이더를 짜다보면 다양한 종류의 쉐이더가 있을 수 있다를 가정하고,
	// 우리만의 네이밍 규칙을 기반으로
	// 어떤 쉐이더가 들어있는지 이해하고 파악된 쉐이더 함수들을 자동 쉐이더로 만들어주는 함수

	// 규칙은 일단 기본적으로 _VS <= 버텍스 쉐이더 함수다를 명확하게 표현하는 이름이어야 한다.
	// 코딩 스탠다드 부터.

	// 이 파일의 경로로
	_File.Open(FileOpenType::Read, FileDataType::Text);

	std::string_view ShaderCode = _File.GetStringView();

	// 파일을 다 읽어 왔고
	// 내부에 어떤 쉐이더가 있는지 분석하기 시작할 것
	{
		// find 앞에서 부터 뒤져서 바이트 위치를 알려준다.
		size_t EntryIndex = ShaderCode.find("_Vs(");
		// 못찾았을 때 나온다.
		if (EntryIndex != std::string::npos)
		{
			// 내가 지정한 위치에서부터 앞으로 찾아가서
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineVertexShader::Load(_File.GetStringPath(), EntryName);

			// ColorShader.fx 픽쉘 쉐이더가 있을 수 있다.
		}
	}

	{
		// find 앞에서 부터 뒤져서 바이트 위치를 알려준다.
		size_t EntryIndex = ShaderCode.find("_PS(");
		// 못 찾았을때 나온다.
		if (EntryIndex != std::string::npos)
		{
			// 내가 지정한 위치에서부터 앞으로 찾기 아서 
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);
			GameEnginePixelShader::Load(_File.GetStringPath(), EntryName);
		}
	}

	return true;
}