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
	MonsterSkill,
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
	MonsterSkill,
	MonsterAttackRange,
	Craving,
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
	GhostSwoo,
	GhostDamien,
	Max,
};