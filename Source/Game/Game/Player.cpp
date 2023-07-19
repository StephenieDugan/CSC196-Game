#include "player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Game/Weapon.h"
#include "Framework/Scene.h"
void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * Twili::g_time.getDeltaTime();

	float thrust = 0;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	Twili::Vector2 forward = Twili::vec2(0, -1).Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * Twili::g_time.getDeltaTime();
	m_transform.position.x = Twili::Wrap(m_transform.position.x, (float)Twili::g_rend.getWidth());
	m_transform.position.y = Twili::Wrap(m_transform.position.y, (float)Twili::g_rend.getHeight());

	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		Twili::Transform transform{ m_transform.position, m_transform.rotation};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 400.0f, transform, m_model );
		m_scene->Add(std::move(weapon));
	}



}

