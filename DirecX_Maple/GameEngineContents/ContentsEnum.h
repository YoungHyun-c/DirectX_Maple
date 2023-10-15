#pragma once

enum class ContentsRenderType
{
	BackGround,
	Play,
	Max,
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
	Max,
};

enum class DeepBufferType
{
	Mouse,
	UI,
	DamageRender,
	JinHillaAnime,
	FrontSkill,
	Player,
	BackSkill,
	Monster,
	MonsterSkill,
	BackGround,
	Max,
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
	Max,
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