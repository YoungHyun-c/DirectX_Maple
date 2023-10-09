#pragma once

enum class ContentsRenderType
{
	BackGround,
	Play,
};

enum class ContentsObjectType
{
	BackGround,
	Monster,
	BackSkill,
	Player,
	FrontSkill,
	JinHillaAnime,
	DamageRender,
	UI,
	Mouse,
};

enum class ContentsCollisionType
{
	Player,
	Monster,
	Skill,
	Potal,
	UI,
	Mouse,
};

enum class ActorDir
{
	Right,
	Left,
	Max,
};

enum class MonstersName
{
	Mugong,
	CarvingMonster,
	GhostSuo,
	GhostDemian,
	Max,
};