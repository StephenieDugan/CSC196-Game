#include "Actor.h"

namespace Twili {
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
			
		}
	}
	void Actor::Draw(Twili::Renderer rend)
{
	m_model.draw(rend, m_transform);
}

}

