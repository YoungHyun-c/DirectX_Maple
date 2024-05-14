#include "PreCompile.h"
#include "ContentsControlWindow.h"
#include "MapEditorLevel.h"
#include "PlayerValue.h"
#include "ContentsTimer.h"

#include "DamageRenderer.h"


#include "Monster.h"
#include "MonsterFunction.h"
#include "CraneMonster.h"

void CharEditorTab::Start()
{
}

void CharEditorTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	Str = PlayerStat->GetValue()->GetPlayerStr();
	Dex = PlayerStat->GetValue()->GetPlayerDex();
	DamagePer = PlayerStat->GetValue()->GetPlayerDamPer();
	FinalDamagePer = PlayerStat->GetValue()->GetPlayerFinalDamPer();
	BossDamagePer = PlayerStat->GetValue()->GetPlayerBossDamPer();
	DefenseIgnore = PlayerStat->GetValue()->GetPlayerDefenseIgnore();
	CritialDam = PlayerStat->GetValue()->GetPlayerCriticalDam();
	AllAttack = PlayerStat->GetValue()->GetPlayerAllAttack();
	AttackPer = PlayerStat->GetValue()->GetPlayerAttackPer();

	DivideLevel = SkillValue::GetValue()->GetDivideLevel();
	MaestroLevel = SkillValue::GetValue()->GetMaestroLevel();
	MugongDefense = MugongStat->GetNeedGlobalValue()->GetMugongDefenseValue();

	if (ImGui::InputInt("Str", &Str))
	{
		if (0 >= Str)
		{
			Str = 1;
		}
		PlayerStat->GetValue()->SetPlayerStr(Str);
	}
	if (ImGui::InputInt("Dex", &Dex))
	{
		if (0 >= Dex)
		{
			Dex = 1;
		}
		PlayerStat->GetValue()->SetPlayerDex(Dex);
	}
	if (ImGui::InputInt("DamagePer", &DamagePer))
	{
		if (0 >= DamagePer)
		{
			DamagePer = 1;
		}
		PlayerStat->GetValue()->SetPlayerDamPer(DamagePer);
	}
	if (ImGui::InputFloat("FinalDamagePer", &FinalDamagePer))
	{
		if (0 >= FinalDamagePer)
		{
			FinalDamagePer = 1;
		}
		PlayerStat->GetValue()->SetPlayerFinalDamPer(FinalDamagePer);
	}
	if (ImGui::InputInt("BossDamagePer", &BossDamagePer))
	{
		if (0 >= BossDamagePer)
		{
			BossDamagePer = 1;
		}
		PlayerStat->GetValue()->SetPlayerBossDamPer(BossDamagePer);
	}
	if (ImGui::InputFloat("DefenseIgnore", &DefenseIgnore))
	{
		if (0 >= DefenseIgnore)
		{
			DefenseIgnore = 1;
		}
		PlayerStat->GetValue()->SetPlayerDefenseIgnore(DefenseIgnore);
	}
	if (ImGui::InputFloat("CritialDam", &CritialDam))
	{
		if (0 >= CritialDam)
		{
			CritialDam = 1;
		}
		PlayerStat->GetValue()->SetPlayerCriticalDam(CritialDam);
	}
	if (ImGui::InputInt("AllAttackPower", &AllAttack))
	{
		if (0 >= AllAttack)
		{
			AllAttack = 1;
		}
		PlayerStat->GetValue()->SetPlayerAllAttack(AllAttack);
	}
	if (ImGui::InputInt("AllAttackPercent %", &AttackPer))
	{
		if (0 >= AttackPer)
		{
			AttackPer = 1;
		}
		PlayerStat->GetValue()->SetPlayerAttackPer(AttackPer);
	}

	if (ImGui::InputInt("6DivideSkillLevel", &DivideLevel))
	{
		if (0 >= DivideLevel)
		{
			DivideLevel = 1;
		}
		if (DivideLevel >= 30)
		{
			DivideLevel = 30;
		}
		SkillValue::GetValue()->SetDivideLevel(DivideLevel);
	}
	if (ImGui::InputInt("MaestroSkillLevel", &MaestroLevel))
	{
		if (0 >= MaestroLevel)
		{
			MaestroLevel = 1;
		}
		if (MaestroLevel >= 30)
		{
			MaestroLevel = 30;
		}
		SkillValue::GetValue()->SetMaestroLevel(MaestroLevel, 110);
	}

	if (ImGui::InputInt("MugongDefense", &MugongDefense))
	{
		if (0 >= MugongDefense)
		{
			MugongDefense = 10;
		}
		MugongStat->GetNeedGlobalValue()->SetMugongDefenseValue(MugongDefense);
	}

	ImGui::Text("SumAllDamage : %llu", GlobalValue::GetNeedGlobalValue()->GetSumDamage());
	ImGui::Text("HitCount : %d", GlobalValue::GetNeedGlobalValue()->GetHitCount());
	
	if (ImGui::Button("Damage Clear"))
	{
		GlobalValue::GetNeedGlobalValue()->ClearDamage();
	}

	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

}

void TestTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	// 시간 세팅은 보류
	//CurTime = ContentsTime->TimeValue;
	//float SetMinute = static_cast<int>(CurTime) / 60;
	//float SetSecond = static_cast<int>(CurTime) % 60;

	//if (ImGui::InputFloat("Set Minute :", &SetMinute))
	//{
	//	if (0 >= SetMinute)
	//	{
	//		SetMinute = 1;
	//	}
	//	{
	//		ContentsTime->SetTimeValue(SetMinute * 60);
	//	}
	//}
	////ImGui::SameLine();
	//if (ImGui::InputFloat("Sec :", &SetSecond))
	//{
	//	if (0 >= SetSecond)
	//	{
	//		SetSecond = 1;
	//	}
	//	{
	//		ContentsTime->SetTimeValue(SetMinute * 60 + SetSecond);
	//	}
	//}

	SickleCutTime = GlobalValue::GetNeedGlobalValue()->GetSickleCutTime();
	int Minute = static_cast<int>(SickleCutTime) / 60;
	int Second = static_cast<int>(SickleCutTime) % 60;

	ImGui::Text("SickleCutTime : %d Minute", Minute);
	ImGui::SameLine();
	ImGui::Text("%d Sec", Second);


	//std::list<std::shared_ptr<GameEngineObject>> ObjectLists = _Level->GetObjectGroupInt(0);

	//std::vector<std::shared_ptr<GameEngineObject>> Objects;

	//for (std::shared_ptr<GameEngineObject> Ptr : ObjectLists)
	//{
	//	Objects.push_back(Ptr);
	//}


	//if (Objects.size())
	//{
	//	std::vector<std::string> Names;

	//	for (std::shared_ptr<GameEngineObject> Ptr : Objects)
	//	{
	//		Names.push_back(Ptr->GetName());
	//	}

	//	std::vector<const char*> CNames;

	//	for (size_t i = 0; i < Names.size(); i++)
	//	{
	//		CNames.push_back(Names[i].c_str());
	//	}

	//	if (ImGui::ListBox("ObjectList", &Select, &CNames[0], static_cast<int>(Names.size())))
	//	{
	//		SelectObject = Objects[Select];
	//	}

	//	if (nullptr != SelectObject)
	//	{
	//		if (ImGui::Button("Select Object Off"))
	//		{
	//			SelectObject->Off();
	//		}

	//	}
	//}


}


void ContentsControlWindow::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("LevelChangeTab"));
	CurTab = Tabs[0];
	Tabs.push_back(std::make_shared<CharEditorTab>("CharEditor"));
	Tabs.push_back(std::make_shared<TestTab>("BossTab"));
	Tabs.push_back(std::make_shared<MapEditorTab>("MapEditor"));
}

void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> Pair : AllLevels)
	{
		if (ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}
	}
}


void MapEditorTab::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	if (ImGui::Button("Save"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("MapDataFile");

		OPENFILENAMEA OFN;
		char filePathName[100] = "";
		char lpstrFile[100] = "";
		static char filter[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		std::string Path = Dir.GetStringPath();

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = "MapData";
		OFN.lpstrInitialDir = Path.c_str();

		if (GetSaveFileNameA(&OFN) != 0) {
			SavePath = OFN.lpstrFile;
		}
	}

	MapEditorLevel* MapLevel = dynamic_cast<MapEditorLevel*>(_Level);

	if ("" != SavePath)
	{
		ImGui::Text(SavePath.c_str());

		if (ImGui::Button("MapDataSave"))
		{
			GameEngineSerializer BinSer;
			BinSer << MapLevel->BackGroundRenderer->GetSprite()->GetName();
			std::vector<std::shared_ptr<CraneMonster>> ObjectType = _Level->GetObjectGroupConvert<CraneMonster>(ContentsObjectType::Monster);
			BinSer << static_cast<unsigned int>(ObjectType.size());
			for (size_t i = 0; i < ObjectType.size(); i++)
			{
				ObjectType[i]->Serializer(BinSer);
			}

			GameEngineFile File = SavePath;
			File.Open(FileOpenType::Write, FileDataType::Binary);
			File.Write(BinSer);

		}
	}

	if (ImGui::Button("Load"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("MapDataFile");

		OPENFILENAMEA OFN;
		char FilePathNam[100] = "";
		char LpStrFile[100] = "";
		static char Filter[] = "모든파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		std::string Path = Dir.GetStringPath();

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
		OFN.lpstrFilter = Filter;
		OFN.lpstrFile = LpStrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = "MapData";
		OFN.lpstrInitialDir = Path.c_str();

		if (GetOpenFileNameA(&OFN) != 0)
		{
			LoadPath = OFN.lpstrFile;
		}
	}

	if (LoadPath != "")
	{
		ImGui::Text(LoadPath.c_str());

		if (ImGui::Button("MapDataLoad"))
		{
			GameEngineSerializer BinSer;

			GameEngineFile File = LoadPath;
			File.Open(FileOpenType::Read, FileDataType::Binary);
			File.DataAllRead(BinSer);

			std::vector<std::shared_ptr<CraneMonster>> ObjectType = _Level->GetObjectGroupConvert<CraneMonster>(ContentsObjectType::Monster);

			for (size_t i = 0; i < ObjectType.size(); i++)
			{
				ObjectType[i]->Death();
			}

			std::string BackFileName;
			BinSer >> BackFileName;
			unsigned int MonsterCount = 0;
			BinSer >> MonsterCount;

			for (size_t i = 0; i < MonsterCount; i++)
			{
				std::shared_ptr<CraneMonster> Object = _Level->CreateActor<CraneMonster>(ContentsObjectType::Monster);
				Object->DeSerializer(BinSer);
				Object->SetDebugMap("HuntDebugMap.png");
			}
		}
	}
}


void ContentsControlWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	for (size_t i = 0; i < Tabs.size(); i++)
	{
		ImGui::SameLine();
		if (ImGui::Button(Tabs[i]->Name.c_str()))
		{
			CurTab = Tabs[i];
			CurTab->Start();
		}
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _DeltaTime);
	}
}
