#include "include.h"

//Randon Functions
int RandomInt(int from, int to){
	return from + (rand() % ((to - from) + 1));
}

float RandomFloat(float from, float to){
	return from + (to - from) * rand() / ((float)RAND_MAX);
}

float Random(){
	return RandomFloat(0.0f, 1.0f);
}