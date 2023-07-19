#pragma once
#include "FrameWork/Actor.h"
class Player : public Twili::Actor
{
public:
	Player(float speed, float turnRate, const Twili::Transform& transform, const Twili::Model& model) :
		Actor{ transform, model }, m_speed{ speed }, m_turnRate{turnRate} {};

	void Update(float dt) override;


protected:
	float m_speed = 0;
	float m_turnRate = 0;
};