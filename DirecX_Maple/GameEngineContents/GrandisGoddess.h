#pragma once

// Ό³Έν :
class GrandisGoddess
{
public:
	// constructer destructer
	GrandisGoddess();
	~GrandisGoddess();

	// delete Function
	GrandisGoddess(const GrandisGoddess& _Other) = delete;
	GrandisGoddess(GrandisGoddess&& _Other) noexcept = delete;
	GrandisGoddess& operator = (const GrandisGoddess& _Other) = delete;
	GrandisGoddess& operator = (GrandisGoddess&& _Other) noexcept = delete;

protected:

private:

};

