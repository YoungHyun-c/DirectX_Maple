#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MonsterSpawnZone : public GameEngineActor
{

public:
	MonsterSpawnZone();
	~MonsterSpawnZone();
	MonsterSpawnZone(const MonsterSpawnZone& _Other) = delete;
	MonsterSpawnZone(MonsterSpawnZone&& _Other) noexcept = delete;
	MonsterSpawnZone& operator=(const MonsterSpawnZone& _Other) = delete;
	MonsterSpawnZone& operator=(MonsterSpawnZone&& _Other) noexcept = delete;

	void MonsterNumUp(int _MonsterName)
	{
		MonsterNum[_MonsterName]->CurNum++;
	}

	void MonsterNumDown(int _MonsterName)
	{
		if (MonsterNum[_MonsterName]->CurNum <= 0)
		{
			MsgBoxAssert("SpawnZone에 기록된 몬스터 액터의 숫자가 0이하입니다. 호출함수 MonsterSpawnZone::NumOfMonsterDown ");
		}

		MonsterNum[_MonsterName]->CurNum--;
	}

	void AllMonsterDeath();

	template<typename EnumType>
	void SetMonsterToZone(EnumType _MonsterName, int _MaxNumber)
	{
		MonsterNum[static_cast<int>(_MonsterName)] = std::make_shared<MonsterInfo>();
		MonsterNum[static_cast<int>(_MonsterName)]->MonsterList.reserve(_MaxNumber);
		MonsterNum[static_cast<int>(_MonsterName)]->MaxNum = _MaxNumber;
		MonsterNum[static_cast<int>(_MonsterName)]->CurNum = 0;
	}

	void SetZonePosAndScale(float4 _Pos, float _Length)
	{
		Transform.SetLocalPosition(_Pos);
		XRange = _Length;
	}

	void SetColMap(const std::string_view& _ColMapName)
	{
		ColMapName = _ColMapName;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;

private:
	void SpawnUpdate();
	void SpawnMonster(int _MonsterName);

	// 몬스터이름, 최대 수 , 현재 수
	struct MonsterInfo {
		std::vector<std::shared_ptr<class MonsterFunction>> MonsterList;

		int MaxNum = 0;
		int CurNum = 0;
	};

	std::map<int, std::shared_ptr<MonsterInfo>> MonsterNum;
	std::string ColMapName = "";
	float XRange = 0.0f;
};

