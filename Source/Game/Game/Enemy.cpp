#include "Enemy.h"
#include "FrameWork/Scene.h"
#include "player.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->getActor<Player>();
	if (player)
	{
		Twili::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.angle() + Twili::halfPi;
	}

	Twili::Vector2 forward = Twili::vec2(0, -1).Rotate(m_transform.rotation);
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
	if (other->m_tag == "PlayerFire" || other->m_tag == "Player")
	{
		m_health -= 5;
	}
	if(m_health <= 0) m_destroyed = true;
}
