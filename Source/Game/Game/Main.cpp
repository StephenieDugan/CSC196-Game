#include <iostream>
#include "../../Engine/Core/Random.h"
#include "../../Engine/Core/FileIO.h"

int main() {

    std::cout << Twili::getFilePath() << std::endl;

    Twili::seedRandom((unsigned int)time(nullptr));
    for (int i = 0; i < 10; i++) {
        std::cout << Twili::random(5, 10) << std::endl;
    }

};