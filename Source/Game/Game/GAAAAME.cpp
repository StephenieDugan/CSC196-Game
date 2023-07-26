#include "GAAAAME.h"
#include "player.h"
#include "Enemy.h"

#include "FrameWork/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"


bool GAAAAME::Init()
{
    //Create Font/text Objects
    font = std::make_shared<Twili::Font>("arcadeclassic.ttf", 24);
    m_Scoretext = std::make_unique<Twili::Text>(font);
    m_Scoretext->Create(Twili::g_rend, "Score 0000", Twili::Color{ 1, 0, 1, 1 });

    m_Livestext = std::make_unique<Twili::Text>(font);
    m_Livestext->Create(Twili::g_rend, "Lives:", Twili::Color{ 1, 0, 1, 1 });

    m_Titletext = std::make_unique<Twili::Text>(font);
    m_Titletext->Create(Twili::g_rend, "Asteroids", Twili::Color{ 1, 1, 1, 1 });

    m_GOvertext = std::make_unique<Twili::Text>(font);
    m_GOvertext->Create(Twili::g_rend, "Game Over", Twili::Color{ 1, 1, 1, 1 });

    Twili::g_noise.AddAudio("Jump", "Jump.wav");


    m_scene = std::make_unique<Twili::Scene>();

	return true;
}

void GAAAAME::ShutDown()
{
}

void GAAAAME::Update(float dt)
{
	switch (m_state)
    {
    case GAAAAME::eState::Title:
      
        if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StartGame;
        }
        break;
    case GAAAAME::eState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_state = eState::StartLevel;
        break;
    case GAAAAME::eState::StartLevel: 
        m_scene->RemoveAll();
    { 
       
        std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, Twili::pi, Twili::Transform{ {400, 300}, 0, 6 }, Twili::g_MM.get("ship.txt"));
        player->m_tag = "Player";
        player->m_game = this;
        player->setDamping(0.9f);
        m_scene->Add(std::move(player));
    }
    m_state = eState::Game;
        break;
    case GAAAAME::eState::Game:

        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Twili::randomF(75.0f, 150.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 6 }, Twili::g_MM.get("enemy.txt"));
            enemy->m_tag = "Enemy";
            enemy->m_game = this;
            m_scene->Add(std::move(enemy));
        }
        break;
    case GAAAAME::eState::PlayerDeadStart:
        m_stateTimer = 3;
        if (m_lives == 0) m_state = eState::GameOverStart;
            else m_state = eState::PlayerDead;
        break;
    case GAAAAME::eState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
         m_state = eState::StartLevel;
        }
        break;
    case GAAAAME::eState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_scene->RemoveAll();
            m_state = eState::Title;
        }
        break;
    default:
        break;
    }

    m_Scoretext->Create(Twili::g_rend, "Score:  " + std::to_string(m_score), {1,1,1,1});
    m_Livestext->Create(Twili::g_rend, "Lives:  " + std::to_string(m_lives), { 1,1,1,1 });

    m_scene->Update(dt);


}

void GAAAAME::Draw(Twili::Renderer& r)
{
    if (m_state == eState::Title)
    {
        m_Titletext->Draw(r, 400, 300);
    }
    if (m_state == eState::GameOverStart)
    {
        m_GOvertext->Draw(r, 400, 300);
    }

    m_Scoretext->Draw(r, 40, 20);
    m_Livestext->Draw(r, 40, 40);
    m_scene->Draw(r);
}
