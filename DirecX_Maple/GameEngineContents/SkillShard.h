#pragma once


// Ό³Έν :
class SkillShard
{
public:
	// constructer destructer
	SkillShard();
	~SkillShard();

	// delete Function
	SkillShard(const SkillShard& _Other) = delete;
	SkillShard(SkillShard&& _Other) noexcept = delete;
	SkillShard& operator = (const SkillShard& _Other) = delete;
	SkillShard& operator = (SkillShard&& _Other) noexcept = delete;

protected:

private:

};

