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
	UI,
};

enum class ContentsCollisionType
{
	Player,
	Monster,
};

enum class ActorDir
{
	Right,
	Left,
	Max,
};