#pragma once
#include "Core/Core.h"
#include <vector>
#include "Renderer.h"


namespace Twili
{
class Model
{
public:

	Model() = default;
	Model(const std::vector<vec2>& points) : m_points{ points } {};

	void draw(Renderer& r);


private:
	std::vector<vec2> m_points;





};


}






