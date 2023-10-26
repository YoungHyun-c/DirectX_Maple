#pragma once


// Ό³Έν :
class BossSkillManager
{
public:
	// constructer destructer
	BossSkillManager();
	~BossSkillManager();

	// delete Function
	BossSkillManager(const BossSkillManager& _Other) = delete;
	BossSkillManager(BossSkillManager&& _Other) noexcept = delete;
	BossSkillManager& operator = (const BossSkillManager& _Other) = delete;
	BossSkillManager& operator = (BossSkillManager&& _Other) noexcept = delete;

protected:

private:

};

