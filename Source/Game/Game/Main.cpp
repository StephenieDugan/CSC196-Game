#include <iostream>
#include <chrono>
#include "Core\Random.h"
#include "Core\FileIO.h"
#include "Core\Memory.h"

using namespace std;


int main() {

	Twili::g_memoryTracker.Display();
	int* p = new int;
	Twili::g_memoryTracker.Display();
	       delete p;
	Twili::g_memoryTracker.Display();
	
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < 10000000; i++) {}

	auto end = std::chrono::high_resolution_clock::now();
	cout << (end - start).count() << endl;




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