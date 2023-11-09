#include "Precompile.h"
#include "MonsterSpawnZone.h"
#include "CraneMonster.h"

MonsterSpawnZone::MonsterSpawnZone()
{
}

MonsterSpawnZone::~MonsterSpawnZone()
{
}

void MonsterSpawnZone::Start()
{

}

void MonsterSpawnZone::Update(float _Delta)
{
	SpawnUpdate();
}


void MonsterSpawnZone::SpawnUpdate()
{
	std::map<int, std::shared_ptr<MonsterInfo>>::iterator Start = MonsterNum.begin();
	std::map<int, std::shared_ptr<MonsterInfo>>::iterator End = MonsterNum.end();

	for (; Start != End; Start++)
	{
		if (Start->second == nullptr)
		{
			continue;
		}

		if (Start->second->MaxNum > Start->second->CurNum)
		{
			SpawnMonster(Start->first);
		}
	}
}

GameEngineRandom MonsterSpawnRandom;

void MonsterSpawnZone::SpawnMonster(int _MonsterName)
{
	switch (_MonsterName)
	{
	case static_cast<int>(MonstersName::Crane):
	{
		std::shared_ptr<CraneMonster> _Crane = GetLevel()->CreateActor<CraneMonster>();
		_Crane->SetMyZone(this, &MonsterSpawnZone::MonsterNumUp);
		_Crane->SetDebugMap(ColMapName);

		TransformData ZoneData = Transform.GetConstTransformDataRef();
		float SpawnXpos = MonsterSpawnRandom.RandomFloat(-XRange, XRange);
		_Crane->Transform.SetLocalPosition({ ZoneData.WorldPosition.X + SpawnXpos, ZoneData.WorldPosition.Y });

		MonsterNum[static_cast<int>(MonstersName::Crane)]->MonsterList.push_back(_Crane->GetDynamic_Cast_This<MonsterFunction>());
	}
		break;
	default:
		break;
	}
}


void MonsterSpawnZone::AllMonsterDeath()
{
	std::map<int, std::shared_ptr<MonsterInfo>>::iterator Start = MonsterNum.begin();
	std::map<int, std::shared_ptr<MonsterInfo>>::iterator End = MonsterNum.end();

	for (; Start != End; Start++)
	{
		if (Start->second == nullptr)
		{
			continue;
		}

		size_t Size = Start->second->MonsterList.size();

		for (int i = 0; i < Size; i++)
		{
			Start->second->MonsterList[i]->Death();
			Start->second->MonsterList[i] = nullptr;
		}
	}
}