//#pragma once
//#include <GameEngineCore/GameEngineActor.h>
//
//// Ό³Έν :
//class JinHillaEnterAnime : public GameEngineActor
//{
//public:
//	static JinHillaEnterAnime* EnterAnime;
//public:
//	// constructer destructer
//	JinHillaEnterAnime();
//	~JinHillaEnterAnime();
//
//	// delete Function
//	JinHillaEnterAnime(const JinHillaEnterAnime& _Other) = delete;
//	JinHillaEnterAnime(JinHillaEnterAnime&& _Other) noexcept = delete;
//	JinHillaEnterAnime& operator = (const JinHillaEnterAnime& _Other) = delete;
//	JinHillaEnterAnime& operator = (JinHillaEnterAnime&& _Other) noexcept = delete;
//
//	const bool GetEnterAniEnd()
//	{
//		return AniEnd;
//	}
//
//protected:
//	void Start() override;
//	void Update(float _Delta) override;
//
//private:
//	std::shared_ptr<GameEngineUIRenderer> JinHillaEnterAni;
//	bool AniEnd = false;
//};
//
