#include "PreCompile.h"
#include <GameEngineBase\GameEngineRandom.h>

#include "SkillManager.h"
#include "AdeleSkill.h"

SkillManager* SkillManager::PlayerSkillManager = nullptr;


SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}


void SkillManager::LevelStart(class GameEngineLevel* _PrevLevel)
{
	PlayerSkillManager = this;
}

void SkillManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void SkillManager::Start()
{

}

void SkillManager::Update(float _Delta)
{

}