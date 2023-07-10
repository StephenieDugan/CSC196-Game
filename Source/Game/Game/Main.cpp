#include <iostream>
#include <chrono>
#include "Renderer\Renderer.h"
#include "Core\Core.h"
#include <vector>
using namespace std;

class Star
{
public:
	Star(Twili::Vector2& pos, Twili::Vector2& vel) : m_pos{pos}, velocity{ vel } {}
	void Update() { m_pos += velocity; }

public:
	Twili::Vector2 m_pos;
	Twili::Vector2 velocity;
};



int main(int argc, char* argv[]) {

	Twili::seedRandom((unsigned) time(nullptr));

	Twili::Renderer renderer;
	renderer.Init();
	renderer.CreateWindow("CSC196", 800, 600);

	Twili::Vector2 pos(Twili::randomF(renderer.getWidth()), Twili::randomF(renderer.getHeight()));
	vector<Star> stars;

	for (int i = 0; i < 1000; i++) {
		Twili::Vector2 pos(Twili::Vector2(Twili::random(renderer.getWidth()), Twili::random(renderer.getHeight())));
		Twili::Vector2 velocity(Twili::randomF(1, 4), 0.0f);
		stars.push_back(Star(pos,velocity));

	}
		
	while (1)
	{
		renderer.setColor(0, 0, 0, 0);
		renderer.beginFrame();

		Twili::Vector2 vel(1.0f, 3.0f);

		for (auto& star : stars)
		{
			star.Update();

			//star.m_pos.x + 1;
			star.m_pos.y += 0.3f;

			if (star.m_pos.x >= renderer.getWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= renderer.getHeight()) star.m_pos.y = 0;

			//renderer.setColor(Twili::random(256), 255, 255, 255);
			renderer.setColor(Twili::random(256), Twili::random(256), Twili::random(256), 255);//draw
			renderer.drawPoint(star.m_pos.x,star.m_pos.y);

		}




		//for(int i = 0; i<1001;i++)
		//{
		//renderer.setColor(Twili::random(256), Twili::random(256), Twili::random(256), 255);//draw
		//renderer.drawPoint(Twili::random(renderer.getWidth()), Twili::random(renderer.getHeight()));
		//renderer.drawLine(Twili::random(renderer.getWidth()), Twili::random(renderer.getHeight()), Twili::random(renderer.getWidth()), Twili::random(renderer.getHeight()));
		//}
		
		renderer.EndFrame();
	}; //pause	
	
	
	/*Twili::g_memoryTracker.Display();
	int* p = new int;
	Twili::g_memoryTracker.Display();
	       delete p;
	Twili::g_memoryTracker.Display();
	
	Twili::Time timer;
	for(int i = 0; i < 100000000; i++) {}
	cout << timer.GetElapsedSeconds() << endl;*/

	

	


	/*


	   cout << Twili::getFilePath() << std::endl;
	   Twili::setFilePath("Assets");
	   cout << Twili::getFilePath() << std::endl;
	   size_t size;
	   Twili::getFileSize("game.txt", size);
	   cout << size << endl;

	   std::string s;
	   Twili::readFile("game.txt",s);
	   cout << s << endl;

	   Twili::seedRandom((unsigned int)time(nullptr));
	   for (int i = 0; i < 10; i++) {
	       std::cout << Twili::random(5, 10) << std::endl;
	   }*/

};