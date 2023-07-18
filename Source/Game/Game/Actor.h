#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
class Actor
{
public:
	Actor() = default;
	Actor(const Twili::Transform& transform, const Twili::Model& model) : m_transform{ transform }, m_model{ model } {}
	virtual void Update(float dt) = 0;
	virtual void Draw(Twili::Renderer rend);

protected:
	Twili::Transform m_transform;
	Twili::Model m_model;
};