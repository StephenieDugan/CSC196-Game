#pragma once
#include <random>

namespace Twili
{
    void seedRandom(unsigned int seed) { srand(seed); }
    int random() { return rand(); }
    int random(unsigned int max) { return rand() % max; }
    int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); }

    float randomF() { return random() / (float) RAND_MAX; }
    float randomF(float max) { return randomF() * max; }
    float randomF(float min,float max) { return min + randomF() * (max - min); }
}

