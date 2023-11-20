#include "PreCompile.h"
#include "ContentsControlWindow.h"
#include "MapEditorLevel.h"
#include "Monster.h"
#include "PlayerValue.h"
#include "ContentsTimer.h"

#include "DamageRenderer.h"
void CharEditorTab::Start()
{
}

void CharEditorTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	Str = PlayerStat->GetValue()->GetPlayerStr();
	Dex = PlayerStat->GetValue()->GetPlayerDex();
	DamagePer = PlayerStat->GetValue()->GetPlayerDamPer();
	BossDamagePer = PlayerStat->GetValue()->GetPlayerBossDamPer();
	DefenseIgnore = PlayerStat->GetValue()->GetPlayerDefenseIgnore();
	CritialDam = PlayerStat->GetValue()->GetPlayerCriticalDam();
	AllAttack = PlayerStat->GetValue()->GetPlayerAllAttack();
	AttackPer = PlayerStat->GetValue()->GetPlayerAttackPer();

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

	if (ImGui::InputInt("MugongDefense", &MugongDefense))
	{
		if (0 >= MugongDefense)
		{
			MugongDefense = 10;
		}
		MugongStat->GetNeedGlobalValue()->SetMugongDefenseValue(MugongDefense);
	}

	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	if (ImGui::Button("Save"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("PlayerData");

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
		OFN.lpstrDefExt = "GameData";
		OFN.lpstrInitialDir = Path.c_str();

		if (GetSaveFileNameA(&OFN) != 0) {
			SavePath = OFN.lpstrFile;
		}
	}

	//if ("" != SavePath)
	//{
	//	ImGui::Text(SavePath.c_str());

	//	if (ImGui::Button("MapDataSave"))
	//	{
	//		GameEngineSerializer BinSer;

	//		std::vector<std::shared_ptr<Monster>> ObjectType = _Level->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);
	//		BinSer << static_cast<unsigned int>(ObjectType.size());
	//		for (size_t i = 0; i < ObjectType.size(); i++)
	//		{
	//			ObjectType[i]->Serializer(BinSer);
	//		}

	//		GameEngineFile File = SavePath;
	//		File.Open(FileOpenType::Write, FileDataType::Binary);
	//		File.Write(BinSer);

	//	}
	//}
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
