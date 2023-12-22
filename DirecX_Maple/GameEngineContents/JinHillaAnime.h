#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class JinHillaAnime : public GameEngineActor
{
public:
	// constructer destructer
	JinHillaAnime();
	~JinHillaAnime();

	// delete Function
	JinHillaAnime(const JinHillaAnime& _Other) = delete;
	JinHillaAnime(JinHillaAnime&& _Other) noexcept = delete;
	JinHillaAnime& operator = (const JinHillaAnime& _Other) = delete;
	JinHillaAnime& operator = (JinHillaAnime&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> JinHillaAnimeRenderer;

	bool JinAnimeEnd = false;

	std::shared_ptr<class GameEngineUIRenderer> DarkRenderer;
};

