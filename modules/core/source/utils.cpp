#include "core.h"

CTweenManager*  g_pTweener = 0;

//Randon Functions
int L_RandomInt(int from, int to){
	return from + (rand() % ((to - from) + 1));
}

float L_RandomFloat(float from, float to){
	return from + (to - from) * rand() / ((float)RAND_MAX);
}

float L_Random(){
	return L_RandomFloat(0.0f, 1.0f);
}

//Bit State Functions
bool L_GetBitState(int flagHolder, int bitState){
	return (flagHolder & bitState) != 0;
}

void L_SetBitState(int *pFlagHolder, int bitState, bool state){
	if (state){
		*pFlagHolder |= bitState;
		return;
	}

	*pFlagHolder &= ~bitState;
}