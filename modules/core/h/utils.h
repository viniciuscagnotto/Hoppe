#ifndef __UTILS_H__
#define __UTILS_H__

extern CTweenManager* g_pTweener;

struct PointFloat{
	float x;
	float y;

	PointFloat(float valX = 0.0f, float valY = 0.0f){
		x = valX;
		y = valY;
	};
};

struct PointInt{
	int x;
	int y;

	PointInt(int valX = 0, int valY = 0){
		x = valX;
		y = valY;
	};
};

//Random Functions
int L_RandomInt(int from, int to);
float L_RandomFloat(float from, float to);
float L_Random();

//Bit State functions
bool L_GetBitState(int flagHolder, int bitState);
void L_SetBitState(int *flagHolder, int bitState, bool state);

#endif //__UTILS_H__