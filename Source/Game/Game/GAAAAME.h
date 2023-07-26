#pragma once
#include "FrameWork/Game.h"
#include "Renderer/Text.h"

class GAAAAME : public Twili::Game
{
public:

	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};


	// Inherited via Game
	virtual bool Init() override;
	virtual void ShutDown() override;

	virtual void Update(float dt) override;
	virtual void Draw(Twili::Renderer& r) override;
	void setState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	std::shared_ptr<Twili::Font> font;
	std::unique_ptr<Twili::Text> m_Scoretext;
	std::unique_ptr<Twili::Text> m_Livestext;
	std::unique_ptr<Twili::Text> m_Healthtext;
	std::unique_ptr<Twili::Text> m_Titletext;
	std::unique_ptr<Twili::Text> m_GOvertext;
	float m_spawn_timer = 0;
	float m_spawnTime = 3;

	float m_stateTimer = 0;


};