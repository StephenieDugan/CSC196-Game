#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"

namespace Twili
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const Twili::Transform& transform, const Twili::Model& model) : m_transform{ transform }, m_model{ model } {}
		virtual void Update(float dt);
		virtual void Draw(Twili::Renderer rend);

		class Scene* m_scene = nullptr;
		friend class Scene;
		Twili::Transform m_transform;
	protected:

		bool m_destroyed = false;
		float m_lifespan = -1.0f;

		
		Twili::Model m_model;

	};

}