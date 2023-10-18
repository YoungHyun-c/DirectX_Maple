#include "PreCompile.h"
#include "PracticeLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "Monster.h"
#include "MainUIActor.h"
#include "TileMap.h"
#include "AdeleSkill.h"
#include "DamageRenderer.h"
#include "SkillManager.h"

#include "Mouse.h"
#include "SummonUi.h"

void TestGUIWindow::Start()
{

}

void TestGUIWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	std::list<std::shared_ptr<GameEngineObject>> ObjectLists = _Level->GetObjectGroupInt(0);

	std::vector<std::shared_ptr<GameEngineObject>> Objects;

	for (std::shared_ptr<GameEngineObject> Ptr : ObjectLists)
	{
		Objects.push_back(Ptr);
	}


	if (Objects.size())
	{
		std::vector<std::string> Names;

		for (std::shared_ptr<GameEngineObject> Ptr : Objects)
		{
			Names.push_back(Ptr->GetName());
		}

		//Names.push_back("aaaa");
		//Names.push_back("bbbb");

		std::vector<const char*> CNames;

		for (size_t i = 0; i < Names.size(); i++)
		{
			CNames.push_back(Names[i].c_str());
		}

		if (ImGui::ListBox("ObjectList", &Select, &CNames[0], Names.size()))
		{
			SelectObject = Objects[Select];
		}

		if (nullptr != SelectObject)
		{
			if (ImGui::Button("Select Object Off"))
			{
				SelectObject->Off();
			}

		}
	}
}

PracticeLevel::PracticeLevel()
{

}

PracticeLevel::~PracticeLevel()
{

}

void PracticeLevel::Start()
{
	GameEngineGUI::CreateGUIWindow<TestGUIWindow>("Test");
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("BackGround");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("PracticeMap.png");
		GameEngineSprite::CreateSingle("PracticeDebugMap.png");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
		GameEngineSprite::CreateSingle("Mugong_stand.png");
	}

	{
		Map = CreateActor<BackGroundMap>(static_cast<int>(ContentsObjectType::BackGround) , "Map");
		Map->Init("PracticeMap.png", "PracticeDebugMap.png");
	}

	{
		PlayerObject = CreateActor<Player>(0, "Player");
		PlayerObject->SetDebugMap("PracticeDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 500.0f, -500.0f, static_cast<float>(DeepBufferType::Player) });
	}

	{
		std::shared_ptr<MainUIActor> UIObject = CreateActor<MainUIActor>(0, "UIObject");
	}

	{
		std::shared_ptr<SummonUi> SummonObject = CreateActor<SummonUi>(0, "SummonButton");
		MouseObject = CreateActor<Mouse>(ContentsObjectType::UI);
	}

	{
		MonsterObject = CreateActor<Monster>(0, "MugongMob");
		MonsterObject->Transform.SetLocalPosition({ 500.0f, -700.0f, static_cast<float>(DeepBufferType::Monster) });
	}

	{
		//std::shared_ptr<AdeleSkill> Skill = CreateActor<AdeleSkill>();
	}

	{
		CreateActor<SkillManager>();
	}

	{
		std::shared_ptr<DamageRenderer> DamageRender = CreateActor<DamageRenderer>();
	}

	GameEngineInput::AddInputObject(this);
	//{
	//	std::shared_ptr<TileMap> Object = CreateActor<TileMap>(ContentsObjectType::BackGround);
}

void PracticeLevel::Update(float _Delta)
{
	//std::string FPS = "FPS : ";
	//FPS += std::to_string(static_cast<int>(1.0f / _Delta));
	//FPS += "\n";
	//OutputDebugStringA(FPS.c_str());

	long long MonsterHp = Monster::Monsters->GetMonsterHp();
	std::string CurMonsterHp = "MonsterHp : ";
	CurMonsterHp += std::to_string(MonsterHp);
	CurMonsterHp += "\n";
	OutputDebugStringA(CurMonsterHp.c_str());


	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('2', this))
	{
		GameEngineCore::ChangeLevel("BossEntranceLevel");
	}


	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	
	if (false == Monster::Monsters->MonsterAppearValue())
	{
		MonsterObject->Transform.SetLocalPosition({ PlayerPos.X, PlayerPos.Y + 100.0f, 100.0f });
	}
}

void PracticeLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("PracticeMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition(HScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	
	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void PracticeLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}