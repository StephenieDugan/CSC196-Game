#include "Actor.h"

void Actor::Draw(Twili::Renderer rend)
{
	m_model.draw(rend, m_transform);
}

