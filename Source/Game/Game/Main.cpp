#include <iostream>
#include <chrono>
#include "Renderer\Renderer.h"
#include "Renderer\Model.h"
#include "Input\InputSystem.h"
#include "Audio\AudioSystem.h"
#include "Core\Core.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <thread>
using namespace std;

class Star
{
public:
	Star(Twili::Vector2& pos, Twili::Vector2& vel) : m_pos{pos}, velocity{ vel } {}
	void Update(int width, int height) {
		m_pos += velocity * Twili::g_time.getDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}
public:
	Twili::Vector2 m_pos;
	Twili::Vector2 velocity;
};



int main(int argc, char* argv[]) {
	int m = Twili::Max(4.0f, 3.0f);
	//int m = Twili::Max(4, 3);

	//constexpr float a = Twili::degreesToRadians(180.0f);

	Twili::seedRandom((unsigned) time(nullptr));
	Twili::setFilePath("assets");

	//Renderer
	Twili::g_rend.Init();
	Twili::g_rend.CreateWindow("CSC196", 800, 600);

	//Input System
	Twili::g_inputSys.Initialize();

	//Audio
	Twili::AudioSystem noise;
	noise.Initialize();

	noise.AddAudio("Jump", "Jump.wav");

	//std::vector<Twili::vec2> points{{0, 0}, { 50,0 }, { 0,50 }, { 0,0 }};
	Twili::Model model;
	model.Load("ship.txt");

	Twili::vec2 v{5, 5};
	v.normalize();


	//Twili::Vector2 pos(Twili::randomF(renderer.getWidth()), Twili::randomF(renderer.getHeight()));
	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		Twili::Vector2 pos(Twili::Vector2(Twili::random(Twili::g_rend.getWidth()), Twili::random(Twili::g_rend.getHeight())));
		Twili::Vector2 velocity(Twili::randomF(1, 4), 0.0f);
		stars.push_back(Star(pos,velocity));

	}

	Twili::Transform transform{{400,300}, 0, 3};
	Twili::vec2 position{400, 300};
	constexpr float turnRate = Twili::degreesToRadians(180);
	float speed = 150;

	Player player{2, Twili::pi, { {400,300}, 0, 10 },model};
	Enemy enemy{ 300, Twili::pi, {{400,300}, Twili::randomF(Twili::pi2), 6}, model };
	//main game code



		bool quit = false;
	while (!quit)
	{
		Twili::g_time.Tick();

		Twili::g_inputSys.Update();
		noise.Update();

		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{

			quit = true;
		}

		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			noise.PlayOneShot("Jump");
		}

		player.Update(Twili::g_time.getDeltaTime());
		enemy.Update(Twili::g_time.getDeltaTime());

		Twili::vec2 direction;
		
		position += direction * speed * Twili::g_time.getDeltaTime();

		Twili::g_rend.setColor(0, 0, 0, 0);
		Twili::g_rend.beginFrame();

		//Twili::Vector2 vel(1.0f, 3.0f);

		for (auto& star : stars)
		{
			star.Update(Twili::g_rend.getWidth(), Twili::g_rend.getHeight());

			star.m_pos.x + 1;
			star.m_pos.y += 0.3f;

			if (star.m_pos.x >= Twili::g_rend.getWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= Twili::g_rend.getHeight()) star.m_pos.y = 0;

			Twili::g_rend.setColor(Twili::random(256), 255, 255, 255);
			Twili::g_rend.setColor(Twili::random(256), Twili::random(256), Twili::random(256), 255);//draw
			Twili::g_rend.drawPoint(star.m_pos.x,star.m_pos.y);

		}
		player.Draw(Twili::g_rend);
		enemy.Draw(Twili::g_rend);

		model.draw(Twili::g_rend, transform.position,transform.rotation,transform.scale);

		Twili::g_rend.EndFrame();

		//for(int i = 0; i<1001;i++)
		//{
		//renderer.setColor(Twili::random(256), Twili::random(256), Twili::random(256), 255);//draw
		//renderer.drawPoint(Twili::random(renderer.getWidth()), Twili::random(renderer.getHeight()));
		//renderer.drawLine(Twili::random(renderer.getWidth()), Twili::random(renderer.getHeight()), Twili::random(renderer.getWidth()), Twili::random(renderer.getHeight()));
		//}
		
		

		//this_thread::sleep_for(chrono::milliseconds(100));
	}; //pause	
	
	return 0;
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