#include <iostream>
#include <chrono>
#include "Renderer\Renderer.h"
#include "Core\Random.h"
#include "Core\FileIO.h"
#include "Core\Memory.h"
#include "Core\Time.h"
using namespace std;


int main() {

	Twili::g_memoryTracker.Display();
	int* p = new int;
	Twili::g_memoryTracker.Display();
	       delete p;
	Twili::g_memoryTracker.Display();
	
	Twili::Time timer;
	for(int i = 0; i < 100000000; i++) {}
	cout << timer.GetElapsedSeconds() << endl;

	

	


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