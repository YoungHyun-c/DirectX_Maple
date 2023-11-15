#include "PreCompile.h"
#include "GlobalValue.h"
#include "ContentsCore.h"

float4 GlobalValue::WinScale = ContentsCore::GetStartWindowSize();
float4 GlobalValue::MapScale;
float4 GlobalValue::CurMonsterPos;

GlobalValue GlobalValue::NeedGlobalValue;

GlobalValue::GlobalValue()
{

}

GlobalValue::~GlobalValue()
{

}
