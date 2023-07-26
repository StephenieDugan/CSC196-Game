#include "Enemy.h"
#include "FrameWork/Scene.h"
#include "player.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "GAAAAME.h"
#include <FrameWork/Emitter.h>
void Enemy::Update(float dt)
{
	Twili::Vector2 forward = Twili::vec2{0, -1}.Rotate(m_transform.rotation);
	Actor::Update(dt);

	Player* player = m_scene->getActor<Player>();
	if (player)
	{
		Twili::Vector2 direction = player->m_transform.position - m_transform.position;
		
		float turnAngle = Twili::vec2::SignedAngle(forward, direction.normalized());
		m_transform.rotation += turnAngle * dt;

		float angle = Twili::vec2::Angle(forward, direction.normalized());
		if (angle < Twili::degreesToRadians(30.0f))
		{
			//i see you 
		}
	}

	
	m_transform.position += forward * m_speed * Twili::g_time.getDeltaTime();
	m_transform.position.x = Twili::Wrap(m_transform.position.x, (float)Twili::g_rend.getWidth());
	m_transform.position.y = Twili::Wrap(m_transform.position.y, (float)Twili::g_rend.getHeight());

	m_fireTimer -= dt;

	if (m_fireTimer <= 0)
	{
		m_fireTimer = m_fireRate;
		Twili::Transform transform{ m_transform.position, m_transform.rotation};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
		weapon->m_tag = "EnemyFire";
		m_scene->Add(std::move(weapon));
		std::cout << "blep";

	}

}

void Enemy::onCollision(Actor* other)
{
	if (other->m_tag == "PlayerFire")
	{
		std::cout << "Blip";
		m_health -= 5;
		if (m_health <= 0) { m_game->AddPoints(100); m_destroyed = true; }

		Twili::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = Twili::pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = Twili::Color{ 1, 1, 0, 1 };
		Twili::Transform transform{ m_transform.position, 0, 1 };
		auto emitter = std::make_unique<Twili::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	
}
