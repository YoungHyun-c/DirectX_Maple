#include "PreCompile.h"
#include "BasicFunction.h"

BasicFunction::BasicFunction()
{

}

BasicFunction::~BasicFunction()
{

}

void BasicFunction::TimeCounting()
{
	CurTime = static_cast<float>(clock());
	TimeCount = (CurTime - PrevTime) / 1000.0f;
	PrevTime = CurTime;
}