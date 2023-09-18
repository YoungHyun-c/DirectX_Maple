#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

class GameEngineShaderResources
{
public :
	std::string Name; // Transformdata <= 쉐이더에서 사용하는 리소스의 이름
	class GameEngineShader* ParentShader; // <= 날 사용하는 쉐이더
	int BindPoint = -1; // <= b0 t0 s0 ... s1 s2 s3, b1 b2 b3 몇번 상수버퍼냐
	
public:
	virtual void Setting() = 0;
	virtual void Reset() = 0;
};

// 이 쉐이더가 상수버퍼를 몇개 사용하냐
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	void Setting() override;
	void Reset() override;
};

// 설명 : 쉐이더 리소스 헬퍼는 2가지 역할을 한다.
//		 1. 특정 쉐이더가 어떤 리소스들을 가지고 있느냐를 조사를 해주는 역할
//		 2. 특정 렌더러가 어떤 리소스들을 세팅해야하는지에 대한 역할 <= 멀티맵(multimap)으로 해야한다.

// 이걸 만들게 된 이뉴는 <= 그런 복잡한 리소스의 구조를 이름으로 통합하기 위해서
// SetConstBuffer(0, TransData);
// => SetConstBuffer("TransformData", TransData);
class GameEngineShaderResHelper
{
public:
	// constructer destructer
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

	// delete Function
	GameEngineShaderResHelper(const GameEngineShaderResHelper& _Other) = delete;
	GameEngineShaderResHelper(GameEngineShaderResHelper&& _Other) noexcept = delete;
	GameEngineShaderResHelper& operator = (const GameEngineShaderResHelper& _Other) = delete;
	GameEngineShaderResHelper& operator = (GameEngineShaderResHelper&& _Other) noexcept = delete;

	// 쉐이더의 컴파일된 코드 결과물
	void ShaderResCheck(std::string _FunctionName, ID3DBlob* _CompileCode);

protected:

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
};

