#pragma once

#include "FrameWork/Actor.h"

class Weapon : public Twili::Actor
{
public:
    Weapon(float speed, const Twili::Transform& transform, const Twili::Model& model) :
        Actor{ transform, model },
        m_speed{ speed }
    {
        m_lifespan = 2.0f;
    }

    void Update(float dt) override;

private:
    float m_speed = 0;
};

