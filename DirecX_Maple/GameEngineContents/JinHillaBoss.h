#pragma once

// Ό³Έν :
class JinHillaBoss
{
public:
	// constructer destructer
	JinHillaBoss();
	~JinHillaBoss();

	// delete Function
	JinHillaBoss(const JinHillaBoss& _Other) = delete;
	JinHillaBoss(JinHillaBoss&& _Other) noexcept = delete;
	JinHillaBoss& operator = (const JinHillaBoss& _Other) = delete;
	JinHillaBoss& operator = (JinHillaBoss&& _Other) noexcept = delete;

protected:

private:
	ActorDir Dir = ActorDir::Max;



};

