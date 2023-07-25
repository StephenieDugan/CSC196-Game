#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
namespace Twili
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const Twili::Transform& transform, std::shared_ptr<Model> model) : m_transform{ transform }, m_model{ model } {};
		virtual void Update(float dt);
		virtual void Draw(Twili::Renderer rend);

		float getRadius() { return m_model->getRadius() * m_transform.scale; };
		virtual void onCollision(Actor* other) {};

		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;
		Twili::Transform m_transform;
		std::string m_tag;

	protected:

		bool m_destroyed = false;
		float m_lifespan = -1.0f;

		
		std::shared_ptr<Model> m_model;

	};

}