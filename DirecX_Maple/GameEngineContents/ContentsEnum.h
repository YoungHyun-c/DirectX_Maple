#pragma once

enum class ContentsRenderType
{
	Fade,
	BackGround,
	Play,
	Max,
};

enum class ContentsObjectType
{
	BackGround,
	Potal,
	Monster,
	MonsterSkill,
	BackSkill,
	Player,
	FrontSkill,
	JinHillaAnime,
	DamageRender,
	DropItem,
	UI,
	JinHillEnteraAnime,
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
	PlayerDropBody,
	Monster,
	Boss,
	MonsterSkill,
	MonsterAttackRange,
	Craving,
	Skill,
	Potal,
	DropItem,
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
	Crane,
	CarvingMonster,
	GhostSwoo,
	GhostDamien,
	Max,
};

enum class ItemType
{
	Equip,
	Use,
	Etc,
};