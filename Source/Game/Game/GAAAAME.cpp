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
    font2 = std::make_shared<Twili::Font>("ThaleahFat.ttf", 80);

    m_Scoretext = std::make_unique<Twili::Text>(font);
    m_Scoretext->Create(Twili::g_rend, "Score 0000", Twili::Color{ 1, 0, 1, 1 });

    m_Livestext = std::make_unique<Twili::Text>(font);
    m_Livestext->Create(Twili::g_rend, "Lives:", Twili::Color{ 1, 0, 1, 1 });

    m_Titletext = std::make_unique<Twili::Text>(font2);
    m_Titletext->Create(Twili::g_rend, "Asteroids", Twili::Color{ 1, 1, 1, 1 });

    m_GOvertext = std::make_unique<Twili::Text>(font2);
    m_GOvertext->Create(Twili::g_rend, "Game Over", Twili::Color{ 1, 1, 1, 1 });

    m_Winnertext = std::make_unique<Twili::Text>(font2);
    m_Winnertext->Create(Twili::g_rend, "You Won!!", Twili::Color{ 1, 1, 1, 1 });

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
        m_state = eState::Level1;
        break;
    case GAAAAME::eState::Level1:

        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Twili::randomF(75.0f, 150.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 5 }, Twili::g_MM.get("enemy.txt"));
            enemy->m_tag = "Enemy";
            enemy->m_game = this;
            m_scene->Add(std::move(enemy));
        }
        if (m_score >= 00)
        {
            m_state = eState::Level2;
        }
        break;
    case GAAAAME::eState::Level2:
    {
        m_spawn_timer += dt;
        for (int i = 0; i < 1; i++) {
            float UpgradePopUp = Twili::randomF(2.0f, 4.0f);
            UpgradePopUp -= dt;
            if (UpgradePopUp <= 0)
            {
                std::unique_ptr<Player> powerup = std::make_unique<Player>(0.0f, 0, Twili::Transform{ {Twili::random(Twili::g_rend.getWidth()), Twili::random(Twili::g_rend.getHeight())}, 0, 3}, Twili::g_MM.get("WeaponUpgrade.txt"));
                powerup->m_tag = "PowerUp";
                powerup->m_game = this;
                m_scene->Add(std::move(powerup));
            }
        }


        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;
            for (int i = 0; i < 2; i++) {
                std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Twili::randomF(80.0f, 160.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 5 }, Twili::g_MM.get("enemy.txt"));
                enemy->m_tag = "Enemy";
                enemy->m_game = this;
                m_scene->Add(std::move(enemy));
            }
            std::unique_ptr<Enemy> enemy2 = std::make_unique<Enemy>(Twili::randomF(85.0f, 170.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 10 }, Twili::g_MM.get("enemy2.txt"));
            enemy2->m_tag = "Enemy2";
            enemy2->m_health = 50.0f;
            enemy2->m_game = this;
            m_scene->Add(std::move(enemy2));
        }
        if (m_score >= 1200)
        {
            m_state = eState::Level3;
        }
    }
        break;
    case GAAAAME::eState::Level3:
        Twili::g_rend.setColor(176, 48, 62, 1);
        m_spawnTime = 4;
        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;
            
            for (int i = 0; i < 4; i++) {
                std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Twili::randomF(80.0f, 160.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 5 }, Twili::g_MM.get("enemy.txt"));
                enemy->m_tag = "Enemy";
                enemy->m_game = this;
                m_scene->Add(std::move(enemy));
            }
            for (int i = 0; i < 4; i++) {
                std::unique_ptr<Enemy> enemy2 = std::make_unique<Enemy>(Twili::randomF(70.0f, 150.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 12 }, Twili::g_MM.get("enemy2.txt"));
                enemy2->m_tag = "Enemy2";
                enemy2->m_health = 80.0f;
                enemy2->m_game = this;

                m_scene->Add(std::move(enemy2));
            }
            std::unique_ptr<Enemy> enemy3 = std::make_unique<Enemy>(Twili::randomF(35.0f, 95.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 16 }, Twili::g_MM.get("enemy2.txt"));
            enemy3->m_tag = "Enemy3";
            enemy3->m_health = 130.0f;
            enemy3->m_game = this;
            m_scene->Add(std::move(enemy3));
        }
        if (m_score >= 2400)
        {
            m_state = eState::Level4;
        }
        break;
    case GAAAAME::eState::Level4:
        m_spawnTime = 6;
        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;

            for (int i = 0; i < 4; i++) {
                std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Twili::randomF(80.0f, 160.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 5 }, Twili::g_MM.get("enemy.txt"));
                enemy->m_tag = "Enemy";
                enemy->m_game = this;
                m_scene->Add(std::move(enemy));
            }
            for (int i = 0; i < 4; i++) {
                std::unique_ptr<Enemy> enemy2 = std::make_unique<Enemy>(Twili::randomF(70.0f, 150.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 13 }, Twili::g_MM.get("enemy2.txt"));
                enemy2->m_tag = "Enemy2";
                enemy2->m_health = 100.0f;
                enemy2->m_game = this;

                m_scene->Add(std::move(enemy2));
            }
            std::unique_ptr<Enemy> enemy3 = std::make_unique<Enemy>(Twili::randomF(35.0f, 95.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 16 }, Twili::g_MM.get("enemy2.txt"));
            enemy3->m_tag = "Enemy3";
            enemy3->m_health = 160.0f;
            enemy3->m_game = this;
            m_scene->Add(std::move(enemy3));
        }
        if (m_score >= 4800)
        {
            m_state = eState::Level5;
        }
        break;
    case GAAAAME::eState::Level5:
        m_spawnTime = 8;
        m_spawn_timer += dt;
        if (m_spawn_timer >= m_spawnTime)
        {
            m_spawn_timer = 0;
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Twili::randomF(75.0f, 150.0f), Twili::pi, Twili::Transform{ {400, 300}, Twili::randomF(Twili::pi2), 6 }, Twili::g_MM.get("enemy.txt"));
            enemy->m_tag = "Enemy";
            enemy->m_game = this;
            m_scene->Add(std::move(enemy));
        }
        if (m_score == 9600)
        {
           
            m_stateTimer = 3;
            m_scene->RemoveAll();
            m_state = eState::WinnerStart;
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
    case GAAAAME::eState::GameOverStart:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::GameOver;
        }
        break;
    case GAAAAME::eState::GameOver:
       
            m_scene->RemoveAll();
            m_state = eState::Title;
       
        break;
    case GAAAAME::eState::WinnerStart:
        
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::Winner;
        }
        break;
    case GAAAAME::eState::Winner:
        m_spawnTime = 3;
        m_state = eState::Title;
        break;
    default:
        break;
    }

    m_Scoretext->Create(Twili::g_rend, "Score:  " + std::to_string(m_score), {1,1,1,1});
    m_Livestext->Create(Twili::g_rend, std::to_string(m_lives) + " :Lives" , { 1,1,1,1 });

    m_scene->Update(dt);


}

void GAAAAME::Draw(Twili::Renderer& r)
{
    if (m_state == eState::Title)
    {
        m_Titletext->Draw(r, 250, 300);
    }
    else if (m_state == eState::GameOverStart)
    {
        m_GOvertext->Draw(r, 250, 300);
    }
    else if (m_state == eState::WinnerStart)
    {
        m_Winnertext->Draw(r, 250, 300);
    }
    else
    {
        m_Scoretext->Draw(r, 40, 20);
        m_Livestext->Draw(r, 680, 20);
    }

    
    m_scene->Draw(r);
}
